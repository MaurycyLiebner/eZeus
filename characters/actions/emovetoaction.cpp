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
    const auto& brd = c->getBoard();
    const auto tp = brd.threadPool();

    if(const auto b = t->underBuilding()) {
        const auto rect = b->tileRect();
        walkable = [walkable, rect](eTileBase* const t) {
            const SDL_Point p{t->x(), t->y()};
            const bool r = SDL_PointInRect(&p, &rect);
            if(r) return true;
            return walkable(t);
        };
    }

    const int tx = t->x();
    const int ty = t->y();

    const auto startTile = [tx, ty](eThreadBoard& board) {
        return board.absTile(tx, ty);
    };

    const stdptr<eMoveToAction> tptr(this);
    const auto failFunc = [tptr]() {
        if(tptr) tptr->setState(eCharacterActionState::failed);
    };
    const auto finishFunc = [tptr, c, failFunc, walkable](
                            const std::vector<eOrientation>& path) {
        if(!tptr) return;
        const auto finishAction = [tptr]() {
            if(tptr) tptr->setState(eCharacterActionState::finished);
        };

        if(path.empty()) {
            finishAction();
            return;
        }

        const auto a  = e::make_shared<eMovePathAction>(
                            c, path, walkable,
                            failFunc, finishAction);
        tptr->setCurrentAction(a);
    };

    const auto pft = new ePathFindTask(startTile, walkable,
                                       final, finishFunc,
                                       failFunc, false, 50);
    tp->queueTask(pft);

    setCurrentAction(e::make_shared<eWaitAction>(c, []() {}, []() {}));
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

void eMoveToAction::start(eBuilding* const final,
                          const eTileWalkable& walkable) {
    const auto rect = final->tileRect();
    const auto finalFunc = [rect](eTileBase* const t) {
        const SDL_Point p{t->x(), t->y()};
        return SDL_PointInRect(&p, &rect);
    };
    start(finalFunc, walkable);
}

void eMoveToAction::start(const eBuildingType final,
                          const eTileWalkable& walkable) {
    const auto finalFunc = [final](eTileBase* const t) {
        return t->underBuildingType() == final;
    };
    start(finalFunc, walkable);
}

bool eMoveToAction::sDefaultWalkable(eTileBase* const t) {
    return t->walkable();
}

bool eMoveToAction::sRoadWalkable(eTileBase* const t) {
    return t->hasRoad();
}
