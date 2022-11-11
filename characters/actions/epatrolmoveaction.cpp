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

eCharacterActionState ePatrolMoveAction::nextTurn(eOrientation& t) {
    if(mWalkedDistance++ > mMaxWalkDistance) {
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
        auto& uses = mOs[tile];
        int min = __INT_MAX__;
        std::vector<eOrientation> minOs;
        minOs.reserve(options.size());
        for(const auto& o : options) {
            const auto oo = o.first;
            int& u = uses.usage(oo);
            if(u < min) {
                minOs.clear();
                minOs.push_back(oo);
                min = u;
            } else if(u == min) {
                minOs.push_back(oo);
            }
        }
        if(!minOs.empty()) {
            const int id = rand() % minOs.size();
            mO = minOs[id];
        }
    }
    t = mO;
    const auto tt = tile->neighbour<eTile>(mO);
    if(!tt) {
        return eCharacterActionState::failed;
    }
    mOs[tile].usage(mO)++;
    mOs[tt].usage(!mO)++;
    return eCharacterActionState::running;
}
