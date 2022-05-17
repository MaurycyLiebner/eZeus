#include "epatrolaction.h"

#include "../echaracter.h"
#include "engine/etile.h"
#include "epatrolmoveaction.h"
#include "buildings/epatrolbuilding.h"

ePatrolAction::ePatrolAction(eCharacter* const c,
                             ePatrolBuilding* const b,
                             const std::vector<ePatrolGuide>& guides,
                             const eAction& failAction,
                             const eAction& finishAction) :
    eActionWithComeback(c, b->centerTile(), failAction, finishAction),
    mGuides(guides), mBuilding(b) {
    setFinishOnComeback(true);
}

bool ePatrolAction::decide() {
    const bool r = eActionWithComeback::decide();
    if(r) return r;
    if(mDone) {
        goBackDecision();
    } else {
        patrol();
    }
    return true;
}

void ePatrolAction::patrol() {
    const auto c = character();
    c->setActionType(eCharacterActionType::walk);
    const auto failFunc = [this]() {
        mDone = true;
        setState(eCharacterActionState::failed);
    };
    const auto finishFunc = [this]() {
        mDone = true;
    };
    if(mGuides.empty()) {
        const auto a = e::make_shared<ePatrolMoveAction>(
                           c, failFunc, finishFunc);
        setCurrentAction(a);
    } else {
        const auto a = e::make_shared<ePatrolGuidedMoveAction>(
                           c, mBuilding, mGuides,
                           failFunc, finishFunc);
        setCurrentAction(a);
    }
}

void ePatrolAction::goBackDecision(const eWalkable& w) {
    goBack(mBuilding, w);
}
