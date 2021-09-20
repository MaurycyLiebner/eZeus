#include "ecollectresourceaction.h"

#include "characters/eresourcecollector.h"
#include "emovetoaction.h"

eCollectResourceAction::eCollectResourceAction(
        const SDL_Rect& buildingRect,
        eResourceCollector* const c,
        const eHasResource& hr,
        const eTranformFunc& tf,
        const eAction& failAction,
        const eAction& finishAction) :
    eActionWithComeback(c, failAction, finishAction),
    mHasResource(hr),
    mTransFunc(tf),
    mCharacter(c),
    mBuildingRect(buildingRect) {
}

void eCollectResourceAction::increment(const int by) {
    if(!currentAction()) findResource();
    else eActionWithComeback::increment(by);
}

void eCollectResourceAction::setCollectedAction(const eTileAction& a) {
    mCollectedAction = a;
}

bool eCollectResourceAction::findResource() {
    const auto c = character();


    const stdptr<eCollectResourceAction> tptr(this);

    const auto failFunc = [this]() {
        setState(eCharacterActionState::failed);
    };

    const auto hr = mHasResource;
        const auto tileWalkable = [hr](eTileBase* const t) {
        return t->walkable() || hr(t);
    };

    const auto hubr = [hr](eTileBase* const t) {
        return hr(t) && !t->busy();
    };
    const auto finishAction = [this, c]() {
        const auto tile = c->tile();
        if(mHasResource(tile) && !tile->busy()) collect(tile);
        else findResource();
    };

    const auto a = e::make_shared<eMoveToAction>(c, failFunc, finishAction);
    const stdptr<eCharacter> cptr(c);
    a->setFoundAction([cptr]() {
        if(!cptr) return;
        cptr->setActionType(eCharacterActionType::walk);
    });
    a->start(hubr, tileWalkable);
    setCurrentAction(a);

    return false;
}

bool eCollectResourceAction::collect(eTile* const tile) {
    tile->setBusy(true);
    mCharacter->setActionType(eCharacterActionType::collect);

    const auto failAction = [this, tile]() {
        tile->setBusy(false);
        setState(eCharacterActionState::failed);
    };
    const auto finishAction = [this, tile]() {
        if(mCollectedAction) mCollectedAction(tile);
        tile->setBusy(false);
        goBack2();
    };

    const auto a = e::make_shared<eCollectAction>(
                       mCharacter, mTransFunc,
                       failAction, finishAction);
    setCurrentAction(a);
    return false;
}

void eCollectResourceAction::goBack2() {
    mCharacter->setActionType(eCharacterActionType::carry);
    const auto hr = mHasResource;
    const auto rect = mBuildingRect;
    eActionWithComeback::goBack([hr, rect](eTileBase* const t) {
        const SDL_Point p{t->x(), t->y()};
        const bool r = SDL_PointInRect(&p, &rect);
        if(r) return true;
        return t->walkable() || hr(t);
    });
}
