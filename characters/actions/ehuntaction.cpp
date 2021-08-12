#include "ehuntaction.h"

#include "engine/epathfinder.h"

eHuntAction::eHuntAction(
        eHunter* const c,
        const eHasResource& hr,
        const eAction& failAction,
        const eAction& finishAction) :
    eActionWithComeback(c, failAction, finishAction),
    mHasResource(hr),
    mCharacter(c) {
}

void eHuntAction::increment(const int by) {
    if(!currentAction()) findResource();
    else eActionWithComeback::increment(by);
}

void eHuntAction::resume() {
    mCharacter->setActionType(mAction);
}

bool eHuntAction::findResource() {
    mAction = eCharacterActionType::walk;
    mCharacter->setActionType(mAction);
    const auto c = character();
    const auto t = c->tile();

    const auto failAction = [this]() {
        setState(eCharacterActionState::failed);
    };
    const auto finishAction = [this, c]() {
        const auto tile = c->tile();
        if(mHasResource(tile)) collect();
        else findResource();
    };

    const auto tileWalkable = [this](eTile* const t) {
        return t->walkable() || mHasResource(t);
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
    mAction = eCharacterActionType::collect;
    mCharacter->setActionType(mAction);

    const auto failAction = [this]() {
        setState(eCharacterActionState::failed);
    };
    const auto finishAction = [this]() {
        goBack2();
    };

    const auto a = new eCollectAction(mCharacter, mTransFunc,
                                      failAction, finishAction);
    setCurrentAction(a);
    return false;
}

bool eHuntAction::goBack2() {
    mAction = eCharacterActionType::carry;
    mCharacter->setActionType(mAction);
    return eActionWithComeback::goBack([this](eTile* const t) {
        return t->walkable() || mHasResource(t);
    });
}
