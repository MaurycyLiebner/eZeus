#include "epatrolmoveaction.h"

#include "../echaracter.h"
#include "engine/etile.h"
#include "emovepathaction.h"
#include "engine/epathfinder.h"

ePatrolMoveAction::ePatrolMoveAction(eCharacter* const c,
                                     const eAction& failAction,
                                     const eAction& finishAction,
                                     const bool diagonalOnly,
                                     const eTileWalkable& walkable) :
    eMoveAction(c, walkable, failAction, finishAction),
    mDiagonalOnly(diagonalOnly),
    mWalkable(walkable) {
    mO = c->orientation();
}

bool ePatrolMoveAction::sRoadWalkable(eTileBase* const tile) {
    return tile->hasRoad();
}

void ePatrolMoveAction::setMaxDistance(const int dist) {
    mMaxDistance = dist;
}

eCharacterActionState ePatrolMoveAction::nextTurn(eOrientation& t) {
    if(mWalkedDistance++ > mMaxDistance) {
        return eCharacterActionState::finished;
    }
    const auto c = character();
    const auto tile = c->tile();
    if(!tile) return eCharacterActionState::failed;

    const auto neighVer = [&](eTileBase* const t) {
        return t && mWalkable(t) && t->neighbour(mO) != tile;
    };
    auto options = mDiagonalOnly ? tile->diagonalNeighbours(neighVer) :
                                   tile->neighbours(neighVer);

    if(options.empty()) {
        mO = !mO;
    } else {
        const int rid = rand() % options.size();
        mO = options[rid].first;
    }
    t = mO;
    const auto tt = tile->neighbour(mO);
    if(!tt) {
        return eCharacterActionState::failed;
    }
    return eCharacterActionState::running;
}
