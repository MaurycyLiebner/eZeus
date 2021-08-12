#include "ehuntaction.h"

#include "engine/epathfinder.h"

eHuntAction::eHuntAction(
        eHunter* const c,
        const eHasResource& hr,
        const eHasCollectableResource& hcr,
        const eAction& failAction,
        const eAction& finishAction) :
    eActionWithComeback(c, failAction, finishAction),
    mHasResource(hr),
    mHasCollectableResource(hcr),
    mCharacter(c) {}

void eHuntAction::increment(const int by) {
    if(!currentAction()) findResource();
    else eActionWithComeback::increment(by);
}

void eHuntAction::resume() {
    eActionWithComeback::resume();
    const auto tile = mCharacter->tile();
    if(mHasCollectableResource(tile)) collect();
}

bool eHuntAction::findResource() {
    mCharacter->setActionType(eCharacterActionType::walk);
    const auto c = character();
    const auto t = c->tile();

    const auto failAction = [this]() {
        setState(eCharacterActionState::failed);
    };
    const auto finishAction = [this, c]() {
        const auto tile = c->tile();
        if(mHasCollectableResource(tile)) collect();
        else findResource();
    };

    const auto tileWalkable = [](eTile* const t) {
        return t->walkable();
    };
    const auto pf0 = ePathFinder(t, tileWalkable, mHasResource);
    std::vector<eOrientation> path0;
    const bool r0 = pf0.findPath(100, path0, false, false);
    if(r0) {
        const auto a  = new eMovePathAction(c, path0, tileWalkable,
                                            failAction, finishAction);
        setCurrentAction(a);
        return true;
    }
    setState(eCharacterActionState::failed);
    return false;
}

bool eHuntAction::collect() {
    mCharacter->incCollected(100);
    goBack2();
    return true;
}

bool eHuntAction::goBack2() {
    mCharacter->setActionType(eCharacterActionType::carry);
    return eActionWithComeback::goBack([](eTile* const t) {
        return t->walkable();
    });
}
