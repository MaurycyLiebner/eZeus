#include "emonsteraction.h"

#include "engine/egameboard.h"

#include "engine/boardData/eheatmaptask.h"
#include "engine/boardData/eheatmapdivisor.h"
#include "buildings/eheatgetters.h"

#include "emovetoaction.h"
#include "ewaitaction.h"
#include "emovearoundaction.h"

#include "audio/esounds.h"
#include "eiteratesquare.h"

eMonsterAction::eMonsterAction(eCharacter* const c,
                               const eAction& failAction,
                               const eAction& finishAction) :
    eGodMonsterAction(c, failAction, finishAction),
    mType(eMonster::sCharacterToMonsterType(c->type())) {}

void eMonsterAction::increment(const int by) {
    const auto c = character();
    const auto at = c->actionType();
    if(at == eCharacterActionType::walk) {
        const int lookForAttackCheck = 8000;

        lookForAttack(by, mLookForAttack, lookForAttackCheck, 10);
    }

    eGodMonsterAction::increment(by);
}

bool eMonsterAction::decide() {
    const auto c = character();
    switch(mStage) {
    case eMonsterAttackStage::none:
        mStage = eMonsterAttackStage::goBack;
        randomPlaceOnBoard();
        if(!c->tile()) c->kill();
        break;
    case eMonsterAttackStage::wait:
        mStage = eMonsterAttackStage::attack;
        goToTarget();
        break;
    case eMonsterAttackStage::attack:
        mStage = eMonsterAttackStage::goBack;
        goBack();
        break;
    case eMonsterAttackStage::goBack:
        mStage = eMonsterAttackStage::wait;
        moveAround();
        break;
    }
    return true;
}


eTile* eMonsterAction::closestEmptySpace(const int rdx, const int rdy) const {
    const auto c = character();
    auto& board = c->getBoard();
    eTile* plainTile = nullptr;
    const auto prcsTile = [&](const int i, const int j) {
        const int tx = rdx + i;
        const int ty = rdy + j;
        const auto tt = board.dtile(tx, ty);
        if(!tt) return false;
        if(!plainTile && tt->walkable()) {
            plainTile = tt;
            return true;
        }
        return false;
    };

    for(int k = 0; k < 1000; k++) {
        eIterateSquare::iterateSquare(k, prcsTile, 1);
    }

    return plainTile;
}

void eMonsterAction::randomPlaceOnBoard() {
    const auto c = character();
    auto& board = c->getBoard();
    const int w = board.width();
    const int h = board.height();
    const int rdx = rand() % w;
    const int rdy = rand() % h;
    const auto tile = closestEmptySpace(rdx, rdy);
    if(!tile) return;
    c->changeTile(tile);
    mHomeTile = tile;
//    const auto c = character();
//    const stdptr<eMonsterAction> tptr(this);
//    const stdptr<eCharacter> cptr(c);
//    const auto hmFinish = [tptr, this, cptr, c](eHeatMap& map) {
//        if(!tptr || !cptr) return;
//        eHeatMapDivisor divisor(map);
//        divisor.divide(10);
//        int tx;
//        int ty;
//        const bool r = divisor.maxHeatTile(tx, ty);
//        if(r) {
//            const auto& board = c->getBoard();
//            c->changeTile(board.tile(tx, ty));
//        } else {
//            setCurrentAction(nullptr);
//        }
//    };
//    const auto hg = eHeatGetters::empty;
//    const auto task = new eHeatMapTask(hg, hmFinish);
//    auto& board = c->getBoard();
//    auto& tp = board.threadPool();
//    tp.queueTask(task);
    //    wait();
}

std::function<bool(eTile* const)> eMonsterAction::obsticleHandler() {
    const stdptr<eMonsterAction> tptr(this);
    return [tptr, this](eTile* const tile) {
        if(!tptr) return false;
        const auto ub = tile->underBuilding();
        if(!ub) return false;
        const auto ubt = ub->type();
        const bool r = eBuilding::sWalkableBuilding(ubt);
        if(r) return false;
        destroyBuilding(ub);
        return true;
    };
}

void eMonsterAction::goToTarget() {
    const stdptr<eMonsterAction> tptr(this);
    const auto tryAgain = [tptr, this](eTile* const tile) {
        (void)tile;
        if(!tptr) return;
        setCurrentAction(nullptr);
    };
    eGodMonsterAction::goToTarget(eHeatGetters::any, tryAgain,
                                  obsticleHandler(),
                                  eWalkableHelpers::sMonsterTileDistance,
                                  eWalkableHelpers::sBuildingsWalkable,
                                  eWalkableHelpers::sDefaultWalkable);
}

void eMonsterAction::goBack() {
    if(!mHomeTile) return setCurrentAction(nullptr);
    const auto c = character();

    const auto a = e::make_shared<eMoveToAction>(
                       c, [](){}, [](){});
    a->setTileDistance(eWalkableHelpers::sMonsterTileDistance);
    a->setObsticleHandler(obsticleHandler());
    a->setFindFailAction([](){});
    a->start(mHomeTile, eWalkableHelpers::sBuildingsWalkable,
             eWalkableHelpers::sDefaultWalkable);
    setCurrentAction(a);
    c->setActionType(eCharacterActionType::walk);
}

void eMonsterAction::destroyBuilding(eBuilding* const b) {
    const auto at = eCharacterActionType::fight;
    const auto tex = &eDestructionTextures::fMonsterMissile;
    const auto playSound = []() {};
    const stdptr<eMonsterAction> tptr(this);
    const stdptr<eBuilding> bptr(b);
    const auto finishAttackA = [tptr, this, bptr]() {
        if(!tptr) return;
        resumeAction();
        if(!bptr) return;
        bptr->collapse();
        eSounds::playCollapseSound();
    };
    pauseAction();
    spawnMultipleMissiles(at, tex, 500, b->centerTile(),
                          playSound, finishAttackA, 3);
}

bool eMonsterAction::lookForAttack(const int dtime,
                                   int& time, const int freq,
                                   const int range) {
    const auto c = character();
    const auto charTarget = std::make_shared<stdptr<eCharacter>>();
    const auto bTarget = std::make_shared<stdptr<eBuilding>>();
    const auto act = [c, charTarget, bTarget](eTile* const t) {
        const auto null = static_cast<eTile*>(nullptr);
        if(c->tile() == t) return null;
        const auto b = t->underBuilding();
        if(b && eBuilding::sAttackable(b->type())) {
            *bTarget = b;
            return b->centerTile();
        } else {
            const auto& chars = t->characters();
            if(chars.empty()) return null;
            for(const auto& cc : chars) {
                if(c == cc.get()) continue;
                bool isGod = false;
                eGod::sCharacterToGodType(cc->type(), &isGod);
                if(isGod) continue;
                bool isMonster = false;
                eMonster::sCharacterToMonsterType(cc->type(), &isMonster);
                if(isMonster) continue;
                bool isHero = false;
                eHero::sCharacterToHeroType(cc->type(), &isHero);
                if(isHero) continue;
                *charTarget = cc;
                return t;
            }
            return null;
        }
    };

    const auto cptr = stdptr<eCharacter>(c);
    const auto finishA = [cptr, charTarget, bTarget]() {
        if(!cptr) return;
        if(*bTarget) {
            (*bTarget)->collapse();
            eSounds::playCollapseSound();
        } else if(*charTarget) {
            (*charTarget)->killWithCorpse();
        }
    };
    const auto at = eCharacterActionType::fight;
    const auto playSound = []() {};
    const auto tex = &eDestructionTextures::fMonsterMissile;

    return lookForRangeAction(dtime, time, freq, range,
                              at, act, tex, playSound, finishA);
}

bool eMonsterAction::lookForRangeAction(const int dtime,
                                        int& time, const int freq,
                                        const int range,
                                        const eCharacterActionType at,
                                        const eMonsterAct& act,
                                        const eTexPtr missileTex,
                                        const eFunc& missileSound,
                                        const eFunc& finishMissileA) {
    const auto c = character();
    const auto cat = c->actionType();
    const bool walking = cat == eCharacterActionType::walk;
    if(!walking) return false;
    auto& brd = c->getBoard();
    const auto ct = c->tile();
    if(!ct) return false;
    const int tx = ct->x();
    const int ty = ct->y();

    time += dtime;
    if(time > freq) {
        time -= freq;
        std::vector<eTile*> tiles;
        const int rr = 2*range + 1;
        tiles.reserve(rr*rr);
        for(int i = -range; i <= range; i++) {
            for(int j = -range; j <= range; j++) {
                const int ttx = tx + i;
                const int tty = ty + j;
                const auto t = brd.tile(ttx, tty);
                if(!t) continue;
                tiles.push_back(t);
            }
        }
        std::random_shuffle(tiles.begin(), tiles.end());
        for(const auto t : tiles) {
            const auto tt = act(t);
            if(!tt) continue;

            const stdptr<eMonsterAction> tptr(this);
            const auto finishAttackA = [tptr, this]() {
                if(!tptr) return;
                resumeAction();
            };

            pauseAction();
            spawnMissile(at, missileTex, 500, tt,
                         missileSound, finishMissileA,
                         finishAttackA);
            return true;
        }
    }
    return false;
}
