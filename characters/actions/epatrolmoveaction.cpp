#include "epatrolmoveaction.h"

#include "../echaracter.h"
#include "engine/etile.h"
#include "emovepathaction.h"
#include "engine/epathfinder.h"

ePatrolMoveAction::ePatrolMoveAction(eCharacter* const c,
                                     const eAction& failAction,
                                     const eAction& finishAction) :
    eMoveAction(c,
                [](eTileBase* const t) {
                    return t->hasRoad();
                },
                failAction, finishAction) {
                    mO = c->orientation();
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

    auto options = tile->diagonalNeighbours(
    [&](eTileBase* const t) {
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
