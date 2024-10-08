#include "epatrolmoveaction.h"

#include "../echaracter.h"
#include "engine/etile.h"
#include "emovepathaction.h"
#include "engine/epathfinder.h"
#include "engine/egameboard.h"

ePatrolMoveAction::ePatrolMoveAction(eCharacter* const c,
                                     const bool diagonalOnly,
                                     const stdsptr<eWalkableObject>& walkable,
                                     const stdsptr<eDirectionTimes>& os) :
    eMoveAction(c, walkable, eCharActionType::patrolMoveAction),
    mDiagonalOnly(diagonalOnly),
    mWalkable(walkable),
    mOs(os) {
    mO = c->orientation();
}

void ePatrolMoveAction::read(eReadStream& src) {
    eMoveAction::read(src);
    src >> mDiagonalOnly;
    mWalkable = src.readWalkable();
    mOs = src.readDirectionTimes(board());
    src >> mO;
    src >> mMaxWalkDistance;
    src >> mWalkedDistance;
}

void ePatrolMoveAction::write(eWriteStream& dst) const {
    eMoveAction::write(dst);
    dst << mDiagonalOnly;
    dst.writeWalkable(mWalkable.get());
    dst.writeDirectionTimes(mOs.get());
    dst << mO;
    dst << mMaxWalkDistance;
    dst << mWalkedDistance;
}

eCharacterActionState ePatrolMoveAction::nextTurn(eOrientation& t) {
    if(mWalkedDistance++ > mMaxWalkDistance) {
        return eCharacterActionState::finished;
    }
    const auto c = character();
    const auto tile = c->tile();
    if(!tile) return eCharacterActionState::failed;

    const auto neighVer = [&](eTileBase* const t) {
        return t && mWalkable->walkable(t) && t->neighbour(mO) != tile;
    };
    auto options = mDiagonalOnly ? tile->diagonalNeighbours(neighVer) :
                                   tile->neighbours(neighVer);
    auto& uses = (*mOs)[tile];
    if(options.empty()) {
        mO = !mO;
    } else {
        int min = __INT_MAX__;
        std::vector<eOrientation> minOs;
        minOs.reserve(options.size());
        for(const auto& o : options) {
            const auto oo = o.first;
            int& u = uses.time(oo);
            if(u < min) {
                minOs.clear();
                minOs.push_back(oo);
                min = u;
            } else if(u == min) {
                minOs.push_back(oo);
            }
        }
        if(!minOs.empty()) {
            const int id = eRand::rand() % minOs.size();
            mO = minOs[id];
        }
    }
    t = mO;
    const auto tt = tile->neighbour<eTile>(mO);
    if(!tt) {
        return eCharacterActionState::failed;
    }
    const auto& board = c->getBoard();
    const int time = board.totalTime();
    if(options.size() > 1) {
        uses.time(mO) = time;
        (*mOs)[tt].time(!mO) = time;
    }
    return eCharacterActionState::running;
}
