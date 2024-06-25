#include "egodworshippedaction.h"

#include "characters/actions/edefendcityaction.h"

eGodWorshippedAction::eGodWorshippedAction(eCharacter* const c) :
    eGodAction(c, eCharActionType::godWorshippedAction) {}

void eGodWorshippedAction::increment(const int by) {
    const int lookForBlessCheck = 6000;
    const int lookForSoldierCheck = 1000;

    const bool r = lookForTargetedBlessCurse(by, mLookForBless,
                                             lookForBlessCheck, 10, 1);
    if(!r) {
        const bool r = lookForSoldierAttack(by, mLookForSoldierAttack,
                                            lookForSoldierCheck, 10);
        if(!r) {
            const int lookForCityDefenseCheck = 5000;
            mLookForCityDefense += by;
            if(mLookForCityDefense > lookForCityDefenseCheck) {
                mLookForCityDefense -= lookForCityDefenseCheck;
                defendCity();
            }
        }
    }

    eGodAction::increment(by);
}

bool eGodWorshippedAction::decide() {
    const auto c = character();
    switch(mStage) {
    case eGodWorshippedStage::none:
        mStage = eGodWorshippedStage::appear;
        if(!c->tile()) randomPlaceOnBoard();
        if(!c->tile()) {
            c->kill();
        } else {
            appear();
        }
        break;
    case eGodWorshippedStage::defend:
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

void eGodWorshippedAction::read(eReadStream& src) {
    eGodAction::read(src);
    src >> mStage;
    src >> mLookForBless;
    src >> mLookForSoldierAttack;
    src >> mLookForCityDefense;
}

void eGodWorshippedAction::write(eWriteStream& dst) const {
    eGodAction::write(dst);
    dst << mStage;
    dst << mLookForBless;
    dst << mLookForSoldierAttack;
    dst << mLookForCityDefense;
}

void eGodWorshippedAction::defendCity() {
    auto& board = eGodWorshippedAction::board();
    const auto i = board.invasionToDefend();
    if(!i) return;
    mStage = eGodWorshippedStage::defend;
    const auto c = character();
    const auto da = e::make_shared<eDefendCityAction>(c);
    setCurrentAction(da);
}
