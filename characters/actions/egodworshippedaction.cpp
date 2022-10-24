#include "egodworshippedaction.h"

#include "buildings/ebuilding.h"
#include "textures/edestructiontextures.h"
#include "esounds.h"

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
        mStage = eGodWorshippedStage::goTo;
        goToTarget();
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
