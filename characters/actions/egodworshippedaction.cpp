#include "egodworshippedaction.h"

#include "characters/echaracter.h"

#include "engine/egameboard.h"

#include "engine/boardData/eheatmaptask.h"
#include "engine/boardData/eheatmapdivisor.h"
#include "buildings/eheatgetters.h"

#include "emovetoaction.h"
#include "ewaitaction.h"

void eGodWorshippedAction::increment(const int by) {
    const int lookForBlessCheck = 6000;

    lookForBlessCurse(by, mLookForBless, lookForBlessCheck, 10, 1.);

    eGodAction::increment(by);
}

bool eGodWorshippedAction::decide() {
    const auto c = character();
    switch(mStage) {
    case eGodWorshippedStage::none:
        mStage = eGodWorshippedStage::appear;
        randomPlaceOnBoard();
        if(!c->tile()) {
            c->kill();
        } else {
            appear();
        }
        break;
    case eGodWorshippedStage::appear:
        mStage = eGodWorshippedStage::goTo;
        goTo();
        break;
    case eGodWorshippedStage::goTo: {
        mStage = eGodWorshippedStage::patrol;
        const auto tile = c->tile();
        if(tile->hasRoad()) patrol();
        else moveAround();
    }   break;
    case eGodWorshippedStage::patrol:
        mStage = eGodWorshippedStage::disappear;
        disappear();
        break;
    case eGodWorshippedStage::disappear:
        c->kill();
        break;
    }
    return true;
}

void eGodWorshippedAction::goTo() {
    const auto c = character();
    const stdptr<eGodWorshippedAction> tptr(this);
    const stdptr<eCharacter> cptr(c);
    const auto hmFinish = [tptr, this, cptr, c](eHeatMap& map) {
        if(!tptr || !cptr) return;
        eHeatMapDivisor divisor(map);
        divisor.divide(10);
        int tx;
        int ty;
        const bool r = divisor.randomHeatTile(tx, ty);
        if(r) {
            const auto tile = closestRoad(tx, ty);
            if(!tile) return setCurrentAction(nullptr);
            const auto tele = [tptr, this, tile]() {
                if(!tptr) return;
                teleport(tile);
            };
            const auto a = e::make_shared<eMoveToAction>(
                               c, tele, [](){});
            a->setFindFailAction(tele);
            a->start(tile);
            setCurrentAction(a);
            c->setActionType(eCharacterActionType::walk);
        } else {
            setCurrentAction(nullptr);
        }
    };
    const auto task = new eHeatMapTask(eHeatGetters::appeal, hmFinish);
    auto& board = c->getBoard();
    auto& tp = board.threadPool();
    tp.queueTask(task);
    wait();
}