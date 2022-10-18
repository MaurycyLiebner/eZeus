#include "egodvisitaction.h"

#include "characters/echaracter.h"

bool eGodVisitAction::decide() {
    const auto c = character();
    switch(mStage) {
    case eGodVisitStage::none:
        mStage = eGodVisitStage::appear;
        randomPlaceOnBoard();
        if(!c->tile()) {
            c->kill();
        } else {
            if(type() == eGodType::hermes) {
                hermesRun(true);
            } else {
                appear();
            }
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
        if(type() == eGodType::hermes) {
            hermesRun(false);
        } else {
            disappear();
        }
        break;
    case eGodVisitStage::disappear:
        c->kill();
        break;
    }
    return true;
}
