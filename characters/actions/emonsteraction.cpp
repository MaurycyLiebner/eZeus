#include "emonsteraction.h"

#include "engine/egameboard.h"

#include "engine/boardData/eheatmaptask.h"
#include "engine/boardData/eheatmapdivisor.h"
#include "buildings/eheatgetters.h"

#include "emovetoaction.h"
#include "ewaitaction.h"
#include "emovearoundaction.h"

#include "esounds.h"
#include "eiteratesquare.h"

eMonsterAction::eMonsterAction(eCharacter* const c,
                               const eAction& failAction,
                               const eAction& finishAction) :
    eGodMonsterAction(c, failAction, finishAction),
    mType(eMonster::sCharacterToMonsterType(c->type())) {}

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

std::function<bool (eTile* const)> eMonsterAction::obsticleHandler() {
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
                                  obsticleHandler());
}

void eMonsterAction::goBack() {
    if(!mHomeTile) return setCurrentAction(nullptr);
    const auto c = character();

    const auto a = e::make_shared<eMoveToAction>(
                       c, [](){}, [](){});
    a->setObsticleHandler(obsticleHandler());
    a->setFindFailAction([](){});
    a->start(mHomeTile);
    setCurrentAction(a);
    c->setActionType(eCharacterActionType::walk);
}

void eMonsterAction::destroyBuilding(eBuilding* const b) {
    const auto at = eCharacterActionType::fight;
    const auto tex = &eDestructionTextures::fMonsterMissile;
    const auto playSound = []() {};
    const stdptr<eMonsterAction> tptr(this);
    const stdptr<eBuilding> bptr(b);
    const auto finishAttackA = [tptr, bptr]() {
        if(!tptr || !bptr) return;
        bptr->collapse();
        eSounds::playCollapseSound();
    };
    spawnMultipleMissiles(at, tex, 500, b->centerTile(),
                          playSound, finishAttackA, 3);
}
