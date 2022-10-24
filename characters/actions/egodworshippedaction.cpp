#include "egodworshippedaction.h"

void eGodWorshippedAction::increment(const int by) {
    const int lookForBlessCheck = 6000;

    lookForBlessCurse(by, mLookForBless, lookForBlessCheck, 10, 1);

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
        mStage = eGodWorshippedStage::goTo1;
        goToTarget();
        break;
    case eGodWorshippedStage::goTo1: {
        mStage = eGodWorshippedStage::patrol1;
        const auto tile = c->tile();
        if(tile->hasRoad()) patrol();
        else moveAround();
    }   break;
    case eGodWorshippedStage::patrol1:
        mStage = eGodWorshippedStage::goTo2;
        goToTarget();
        break;
    case eGodWorshippedStage::goTo2: {
        mStage = eGodWorshippedStage::patrol2;
        const auto tile = c->tile();
        if(tile->hasRoad()) patrol();
        else moveAround();
    }   break;
    case eGodWorshippedStage::patrol2:
        mStage = eGodWorshippedStage::disappear;
        disappear();
        break;
    case eGodWorshippedStage::disappear:
        c->kill();
        break;
    }
    return true;
}
