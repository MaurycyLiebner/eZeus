#include "ecollectresourceaction.h"

#include "characters/eresourcecollector.h"
#include "emovepathaction.h"
#include "engine/epathfinder.h"
#include "epathfindtask.h"
#include "engine/ethreadpool.h"
#include "characters/actions/ewaitaction.h"

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

bool eCollectResourceAction::findResource() {
    const auto c = character();
    const auto t = c->tile();
    const auto& brd = c->getBoard();
    const auto tp = brd.threadPool();

    const int tx = t->x();
    const int ty = t->y();

    const auto startTile = [tx, ty](eThreadBoard& board) {
        return board.absTile(tx, ty);
    };

    const auto hr = mHasResource;

    const auto failFunc = [this]() {
        setState(eCharacterActionState::failed);
    };
    const auto rect = mBuildingRect;
    const auto tileWalkable = [hr, rect](eTileBase* const t) {
        const SDL_Point p{t->x(), t->y()};
        const bool r = SDL_PointInRect(&p, &rect);
        if(r) return true;
        return t->walkable() || hr(t);
    };
    const auto hubr = [hr](eTileBase* const t) {
        return hr(t) && !t->busy();
    };
    const auto finishFunc = [this, c, tileWalkable, failFunc](
                            const std::vector<eOrientation>& path) {
        const auto finishAction = [this, c]() {
            const auto tile = c->tile();
            if(mHasResource(tile) && !tile->busy()) collect(tile);
            else findResource();
        };

        c->setActionType(eCharacterActionType::walk);
        const auto a  = e::make_shared<eMovePathAction>(
                            c, path, tileWalkable,
                            failFunc, finishAction);
        setCurrentAction(a);
    };

    const auto pft = new ePathFindTask(startTile, tileWalkable,
                                       hubr, finishFunc,
                                       failFunc, false, 50);
    tp->queueTask(pft);

    setCurrentAction(e::make_shared<eWaitAction>(c, []() {}, []() {}));
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
