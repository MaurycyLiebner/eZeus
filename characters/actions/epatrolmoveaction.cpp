#include "epatrolmoveaction.h"

#include "../echaracter.h"
#include "engine/etile.h"
#include "emovepathaction.h"
#include "engine/epathfinder.h"

ePatrolMoveAction::ePatrolMoveAction(eCharacter* const c,
                                     const SDL_Rect& buildingRect,
                                     const eAction& failAction,
                                     const eAction& finishAction) :
    eMoveAction(c,
                [buildingRect](eTileBase* const t) {
                    const SDL_Point p{t->x(), t->y()};
                    const bool r = SDL_PointInRect(&p, &buildingRect);
                    if(r) return true;
                    return t->hasRoad();
                },
                failAction, finishAction),
    mBuildingRect(buildingRect) {
    mO = c->orientation();
}

eCharacterActionState ePatrolMoveAction::nextTurn(eOrientation& t) {
    if(mWalkedDistance++ > mMaxDistance) {
        setState(eCharacterActionState::finished);
        return eCharacterActionState::finished;
    }
    const auto c = character();
    const auto tile = c->tile();
    if(!tile) return eCharacterActionState::failed;

    auto options = tile->diagonalNeighbours(
    [&](eTileBase* const t) {
        const SDL_Point p{t->x(), t->y()};
        const bool r = SDL_PointInRect(&p, &mBuildingRect);
        if(r) return true;
        return t && t->hasRoad() && t->neighbour(mO) != tile;
    });

    if(options.empty()) {
        mO = !mO;
    } else {
        std::random_shuffle(options.begin(), options.end());
        mO = options.front().first;
    }
    t = mO;
    const auto tt = tile->neighbour(mO);
    if(!tt) {
        return eCharacterActionState::failed;
    }
    return eCharacterActionState::running;
}
