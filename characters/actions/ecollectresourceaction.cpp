#include "ecollectresourceaction.h"

#include "characters/eresourcecollector.h"
#include "emovepathaction.h"
#include "engine/epathfinder.h"

eCollectResourceAction::eCollectResourceAction(
        eResourceCollector* const c,
        const eHasResource& hr,
        const eTranformFunc& tf,
        const eAction& failAction,
        const eAction& finishAction,
        const eCollectActionCreator& cac) :
    eActionWithComeback(c, failAction, finishAction),
    mHasResource(hr),
    mTransFunc(tf),
    mCollectCreator(cac),
    mCharacter(c) {
}

void eCollectResourceAction::increment(const int by) {
    if(!currentAction()) findResource();
    else eActionWithComeback::increment(by);
}

bool eCollectResourceAction::findResource() {
    mAction = eResourceCollectorAction::walk;
    mCharacter->setAnimationAction(mAction);
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

bool eCollectResourceAction::collect() {
    mAction = eResourceCollectorAction::collect;
    mCharacter->setAnimationAction(mAction);

    const auto failAction = [this]() {
        setState(eCharacterActionState::failed);
    };
    const auto finishAction = [this]() {
        goBack2();
    };

    const auto a = mCollectCreator(mCharacter, mTransFunc,
                                   failAction, finishAction);
    setCurrentAction(a);
    return false;
}

bool eCollectResourceAction::goBack2() {
    mAction = eResourceCollectorAction::carry;
    mCharacter->setAnimationAction(mAction);
    return eActionWithComeback::goBack([this](eTile* const t) {
        return t->walkable() || mHasResource(t);
    });
}
