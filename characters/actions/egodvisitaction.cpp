#include "egodvisitaction.h"

#include "characters/echaracter.h"

void eGodVisitAction::increment(const int by) {
    const int lookForSoldierCheck = 1500;
    const int lookForBlessCheck = 18000;

    bool r = lookForBlessCurse(by, mLookForBless, lookForBlessCheck, 10, 1);
    if(!r) lookForSoldierAttack(by, mLookForSoldierAttack, lookForSoldierCheck, 10);

    eGodAction::increment(by);
}

bool eGodVisitAction::decide() {
    const auto c = character();
    switch(mStage) {
    case eGodVisitStage::none:
        mStage = eGodVisitStage::appear;
        randomPlaceOnBoard();
        if(!c->tile()) {
            c->kill();
        } else {
            appear();
        }
        break;
    case eGodVisitStage::appear: {
        mStage = eGodVisitStage::patrol;
        const auto tile = c->tile();
        if(tile->hasRoad()) patrol();
        else moveAround();
    }   break;
    case eGodVisitStage::patrol:
        mStage = eGodVisitStage::disappear;
        disappear();
        break;
    case eGodVisitStage::disappear:
        c->kill();
        break;
    }
    return true;
}
