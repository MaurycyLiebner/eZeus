#include "ehuntaction.h"

#include "engine/epathfinder.h"

#include "epathfindtask.h"
#include "engine/ethreadpool.h"
#include "characters/actions/ewaitaction.h"

eHuntAction::eHuntAction(
        const SDL_Rect& buildingRect,
        eHunter* const c,
        const eHasResource& hr,
        const eHasCollectableResource& hcr,
        const eAction& failAction,
        const eAction& finishAction) :
    eActionWithComeback(c, failAction, finishAction),
    mHasResource(hr),
    mHasCollectableResource(hcr),
    mCharacter(c),
    mBuildingRect(buildingRect) {}

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
    const auto c = character();
    const auto t = c->tile();
    const auto& brd = c->board();
    const auto tp = brd.threadPool();

    const int tx = t->x();
    const int ty = t->y();

    const auto startTile = [tx, ty](eThreadBoard& board) {
        return board.absTile(tx, ty);
    };
    const auto rect = mBuildingRect;
    const auto tileWalkable = [rect](eTileBase* const t) {
        const SDL_Point p{t->x(), t->y()};
        const bool r = SDL_PointInRect(&p, &rect);
        if(r) return true;
        return t->walkable();
    };
    const auto failFunc = [this]() {
        setState(eCharacterActionState::failed);
    };
    const auto finishFunc = [this, c, tileWalkable, failFunc](
                            const std::vector<eOrientation>& path) {
        const auto finishAction = [this, c]() {
            const auto tile = c->tile();
            if(mHasCollectableResource(tile)) collect();
            else findResource();
        };

        c->setActionType(eCharacterActionType::walk);
        const auto a  = new eMovePathAction(c, path, tileWalkable,
                                            failFunc, finishAction);
        setCurrentAction(a);
    };

    const auto pft = new ePathFindTask(startTile, tileWalkable,
                                       mHasResource, finishFunc,
                                       failFunc, false, 50);
    tp->queueTask(pft);

    setCurrentAction(new eWaitAction(c, []() {}, []() {}));

    return true;
}

bool eHuntAction::collect() {
    mCharacter->incCollected(1);
    goBack2();
    return true;
}

void eHuntAction::goBack2() {
    mCharacter->setActionType(eCharacterActionType::carry);
    const auto rect = mBuildingRect;
    eActionWithComeback::goBack([rect](eTileBase* const t) {
        const SDL_Point p{t->x(), t->y()};
        const bool r = SDL_PointInRect(&p, &rect);
        if(r) return true;
        return t->walkable();
    });
}
