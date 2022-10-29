#include "emovetoaction.h"

#include "emovepathaction.h"

#include "characters/echaracter.h"
#include "engine/egameboard.h"
#include "engine/thread/ethreadboard.h"
#include "engine/ethreadpool.h"
#include "epathfindtask.h"
#include "ewaitaction.h"

void eMoveToAction::start(const eTileFinal& final,
                          eTileWalkable walkable) {
    const auto c = character();
    const auto t = c->tile();
    auto& brd = c->getBoard();
    auto& tp = brd.threadPool();

    if(const auto b = t->underBuilding()) {
        walkable = eWalkableHelpers::sBuildingWalkable(b, walkable);
    }

    const int tx = t->x();
    const int ty = t->y();

    const auto startTile = [tx, ty](eThreadBoard& board) {
        return board.tile(tx, ty);
    };

    const stdptr<eMoveToAction> tptr(this);
    const auto failFunc = [tptr, this]() {
        if(!tptr) return;
        setState(eCharacterActionState::failed);
    };
    const auto finishFunc = [tptr, this, c, failFunc, walkable](
                            std::vector<eOrientation> path) {
        if(!tptr) return;
        const auto finishAction = [tptr, this]() {
            if(!tptr) return;
            setState(eCharacterActionState::finished);
        };

        if(mRemoveLastTurn && !path.empty()) {
            path.erase(path.begin());
        }
        if(path.empty()) {
            finishAction();
            return;
        }
        mPathLength = path.size();
        if(mFoundAction) mFoundAction();
        if(!tptr) return;
        const auto a  = e::make_shared<eMovePathAction>(
                            c, path, walkable,
                            failFunc, finishAction);
        a->setObsticleHandler(mObstHandler);
        a->setMaxDistance(mMaxWalkDistance);
        setCurrentAction(a);
    };

    const auto findFailFunc = [tptr, this]() {
        if(!tptr) return;
        if(mFindFailAction) mFindFailAction();
        if(!tptr) return;
        setState(eCharacterActionState::failed);
    };

    const auto pft = new ePathFindTask(startTile, walkable,
                                       final, finishFunc,
                                       findFailFunc, mDiagonalOnly,
                                       mMaxFindDistance);
    tp.queueTask(pft);

    if(mWait) {
        const auto w = e::make_shared<eWaitAction>(
                           c, []() {}, []() {});
        setCurrentAction(w);
    }
}

void eMoveToAction::start(eTile* const final,
                          const eTileWalkable& walkable) {
    const int tx = final->x();
    const int ty = final->y();
    const auto finalFunc = [tx, ty](eTileBase* const t) {
        return t->x() == tx && t->y() == ty;
    };
    start(finalFunc, walkable);
}

void eMoveToAction::start(const SDL_Rect& rect,
                          const eTileWalkable& walkable) {
    const auto finalFunc = [rect](eTileBase* const t) {
        const SDL_Point p{t->x(), t->y()};
        return SDL_PointInRect(&p, &rect);
    };
    const auto walkable2 = eWalkableHelpers::sBuildingWalkable(
                              rect, walkable);
    start(finalFunc, walkable2);
}

void eMoveToAction::start(eBuilding* const final,
                          const eTileWalkable& walkable) {
    const auto rect = final->tileRect();
    return start(rect, walkable);
}

void eMoveToAction::start(const eBuildingType final,
                          const eTileWalkable& walkable) {
    const auto finalFunc = [final](eTileBase* const t) {
        return t->underBuildingType() == final;
    };
    start(finalFunc, walkable);
}

void eMoveToAction::setObsticleHandler(const eObsticleHandler& oh) {
    mObstHandler = oh;
}
