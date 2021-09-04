#include "epatrolguidedmoveaction.h"

#include "emovepathaction.h"
#include "../echaracter.h"
#include "engine/egameboard.h"
#include "engine/ethreadpool.h"
#include "epathfindtask.h"
#include "characters/actions/ewaitaction.h"

ePatrolGuidedMoveAction::ePatrolGuidedMoveAction(
        eCharacter* const c,
        const SDL_Rect& buildingRect,
        const std::vector<ePatrolGuide>& guides,
        const eAction& failAction,
        const eAction& finishAction) :
    eComplexAction(c, failAction, finishAction),
    mGuides(guides), mBuildingRect(buildingRect) {

}

void ePatrolGuidedMoveAction::increment(const int by) {
    if(!currentAction()) nextGuide();
    eComplexAction::increment(by);
}

void ePatrolGuidedMoveAction::nextGuide() {
    const int maxG = mGuides.size();
    if(mNextGuide >= maxG) {
        return setState(eCharacterActionState::finished);
    }
    const auto& g = mGuides.at(mNextGuide++);

    const auto c = character();
    const auto t = c->tile();
    const auto& brd = c->board();
    const auto tp = brd.threadPool();

    const int tx = t->x();
    const int ty = t->y();

    const auto startTile = [tx, ty](eThreadBoard& board) {
        return board.absTile(tx, ty);
    };
    const auto finalTile = [g](eThreadTile* const t) {
        return t->x() == g.fX && t->y() == g.fY;
    };
    const stdptr<ePatrolGuidedMoveAction> tptr(this);
    const auto failFunc = [tptr]() {
        if(tptr) tptr->setState(eCharacterActionState::failed);
    };

    const auto rect = mBuildingRect;
    const auto walkable = [rect](eTileBase* const t) {
        const SDL_Point p{t->x(), t->y()};
        const bool r = SDL_PointInRect(&p, &rect);
        if(r) return true;
        return t->hasRoad();
    };

    const auto finishFunc = [tptr, c, walkable, failFunc](
                            const std::vector<eOrientation>& path) {
        if(!tptr) return;
        const auto finishAction = [tptr]() {
            if(tptr) tptr->nextGuide();
        };

        const auto a  = e::make_shared<eMovePathAction>(
                            c, path, walkable,
                            failFunc, finishAction);
        tptr->setCurrentAction(a);
    };

    const auto pft = new ePathFindTask(startTile, walkable,
                                       finalTile, finishFunc,
                                       failFunc, false, 50);
    tp->queueTask(pft);

    setCurrentAction(e::make_shared<eWaitAction>(c, []() {}, []() {}));

}
