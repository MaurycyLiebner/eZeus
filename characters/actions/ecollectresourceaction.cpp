#include "ecollectresourceaction.h"

#include "characters/eresourcecollector.h"
#include "emovepathaction.h"
#include "engine/epathfinder.h"

eCollectResourceAction::eCollectResourceAction(
        eResourceCollector* const c,
        const eHasResource& hr,
        const eTranformFunc& tf,
        const eAction& failAction,
        const eAction& finishAction) :
    eActionWithComeback(c, failAction, finishAction),
    mHasResource(hr),
    mTransFunc(tf),
    mCharacter(c) {
}

void eCollectResourceAction::increment(const int by) {
    if(!currentAction()) findResource();
    else eActionWithComeback::increment(by);
}

void eCollectResourceAction::resume() {
    mCharacter->setActionType(mAction);
}

bool eCollectResourceAction::findResource() {
    mAction = eCharacterActionType::walk;
    mCharacter->setActionType(mAction);
    const auto c = character();
    const auto t = c->tile();

    const auto failAction = [this]() {
        setState(eCharacterActionState::failed);
    };
    const auto finishAction = [this, c]() {
        const auto tile = c->tile();
        if(mHasResource(tile) && !tile->busy()) collect(tile);
        else findResource();
    };

    const auto tileWalkable = [this](eTileBase* const t) {
        return t->walkable() || mHasResource(t);
    };

    const auto hubr = [this](eTileBase* const t) {
        return mHasResource(t) && !t->busy();
    };

    const auto pf0 = ePathFinder(t, tileWalkable, hubr);
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

bool eCollectResourceAction::collect(eTile* const tile) {
    tile->setBusy(true);
    mAction = eCharacterActionType::collect;
    mCharacter->setActionType(mAction);

    const auto failAction = [this, tile]() {
        tile->setBusy(false);
        setState(eCharacterActionState::failed);
    };
    const auto finishAction = [this, tile]() {
        tile->setBusy(false);
        goBack2();
    };

    const auto a = new eCollectAction(mCharacter, mTransFunc,
                                      failAction, finishAction);
    setCurrentAction(a);
    return false;
}

bool eCollectResourceAction::goBack2() {
    mAction = eCharacterActionType::carry;
    mCharacter->setActionType(mAction);
    return eActionWithComeback::goBack([this](eTileBase* const t) {
        return t->walkable() || mHasResource(t);
    });
}
