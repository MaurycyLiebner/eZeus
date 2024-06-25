#include "emonsteraction.h"

#include "engine/egameboard.h"

#include "engine/boardData/eheatmaptask.h"
#include "buildings/eheatgetters.h"

#include "emovetoaction.h"
#include "eiteratesquare.h"

#include "egodaction.h"

eMonsterAction::eMonsterAction(eCharacter* const c) :
    eGodMonsterAction(c, eCharActionType::monsterAction),
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
        mStage = eMonsterAttackStage::wait;
        if(!c->tile()) {
            randomPlaceOnBoard();
            if(!c->tile()) c->kill();
        }
        break;
    case eMonsterAttackStage::wait: {
        mStage = eMonsterAttackStage::goTo;
        goToTarget();
        auto& board = this->board();
        board.updateMusic();
    } break;
    case eMonsterAttackStage::goTo:
        mStage = eMonsterAttackStage::patrol;
        monsterPatrol();
        break;
    case eMonsterAttackStage::patrol:
        mStage = eMonsterAttackStage::goBack;
        goBack();
        break;
    case eMonsterAttackStage::goBack: {
        mStage = eMonsterAttackStage::wait;
        moveAround(nullptr, 100000);
        auto& board = this->board();
        board.updateMusic();
    } break;
    }
    return true;
}

void eMonsterAction::read(eReadStream& src) {
    eGodMonsterAction::read(src);
    mHomeTile = src.readTile(board());
    src >> mStage;
    src >> mLookForAttack;
}

void eMonsterAction::write(eWriteStream& dst) const {
    eGodMonsterAction::write(dst);
    dst.writeTile(mHomeTile);
    dst << mStage;
    dst << mLookForAttack;
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

stdsptr<eObsticleHandler> eMonsterAction::obsticleHandler() {
    return std::make_shared<eMonsterObsticleHandler>(board(), this);
}

void eMonsterAction::goToTarget() {
    if(mType == eMonsterType::scylla ||
       mType == eMonsterType::kraken) {
        const auto c = character();

        const auto underBuilding = [](eTileBase* const tile) {
            const auto type = tile->underBuildingType();
            return eBuilding::sAttackable(type);
        };

        const auto a = e::make_shared<eMoveToAction>(c);
        const stdptr<eMonsterAction> tptr(this);
        a->setFoundAction([tptr, this]() {
            if(!tptr) return;
            const auto c = character();
            c->setActionType(eCharacterActionType::walk);
        });
        a->setRemoveLastTurn(true);

        a->start(underBuilding, eWalkableObject::sCreateWater());
        setCurrentAction(a);
    } else {
        const stdptr<eMonsterAction> tptr(this);
        const auto tryAgain = std::make_shared<eGoToTargetTryAgain>(
                                  board(), this);
        eGodMonsterAction::goToTarget(eHeatGetters::any, tryAgain,
                                      obsticleHandler(),
                                      eWalkableHelpers::sMonsterTileDistance,
                                      eWalkableObject::sCreateTerrain(),
                                      eWalkableObject::sCreateDefault());
    }
}

void eMonsterAction::goBack() {
    if(!mHomeTile) return setCurrentAction(nullptr);
    const auto c = character();

    const auto a = e::make_shared<eMoveToAction>(c);
    a->setTileDistance(eWalkableHelpers::sMonsterTileDistance);
    a->setObsticleHandler(obsticleHandler());
    a->setFindFailAction([](){});
    a->start(mHomeTile, eWalkableObject::sCreateTerrain(),
             eWalkableObject::sCreateDefault());
    setCurrentAction(a);
    c->setActionType(eCharacterActionType::walk);
}

void eMonsterAction::monsterPatrol() {
    if(mType == eMonsterType::scylla ||
       mType == eMonsterType::kraken) {
        moveAround(nullptr, 5000, eWalkableObject::sCreateWater());
    } else {
        goToNearestRoad();
    }
}

void eMonsterAction::destroyBuilding(eBuilding* const b) {
    const auto at = eCharacterActionType::fight;
    const auto c = character();
    const auto chart = c->type();
    const auto finishAttackA = std::make_shared<eMA_destroyBuildingFinish>(
                                   board(), this, b);

    const auto playHitSound = std::make_shared<ePlayMonsterBuildingAttackSoundGodAct>(
                                  board(), b);
    pauseAction();
    spawnMultipleMissiles(at, chart, 500, b->centerTile(),
                          nullptr, playHitSound, finishAttackA, 3);
}

bool eMonsterAction::lookForAttack(const int dtime,
                                   int& time, const int freq,
                                   const int range) {
    const auto c = character();
    const auto act = std::make_shared<eLookForAttackGodAct>(
                         board(), c);

    const auto at = eCharacterActionType::fight;

    return lookForRangeAction(dtime, time, freq, range,
                              at, act, nullptr);
}

bool eMonsterAction::lookForRangeAction(const int dtime,
                                        int& time, const int freq,
                                        const int range,
                                        const eCharacterActionType at,
                                        const stdsptr<eGodAct>& act,
                                        const stdsptr<eCharActFunc>& missileSound) {
    const auto c = character();
    const auto chart = c->type();
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
            const auto tt = act->find(t);
            if(!tt) continue;

            const auto finishAttackA = std::make_shared<eMA_lookForRangeActionFinishAttack>(
                                           board(), this);

            pauseAction();
            const int attackTime = eMonster::sMonsterAttackTime(mType);
            spawnMissile(at, chart, attackTime, tt,
                         missileSound, act, finishAttackA);
            return true;
        }
    }
    return false;
}
