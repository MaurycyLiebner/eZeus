#include "emovearoundaction.h"

#include "characters/echaracter.h"

eMoveAroundAction::eMoveAroundAction(eCharacter* const c,
                                     const eAction& failAction,
                                     const eAction& finishAction,
                                     const int startX, const int startY,
                                     const eTileWalkable& walkable) :
    eMoveAction(c,
                walkable,
                failAction,
                finishAction) {
    mStartTX = startX;
    mStartTY = startY;
}

bool eMoveAroundAction::sDefaultWalkable(eTileBase* const tile) {
    return tile->walkable();
}

bool eMoveAroundAction::sFertileWalkable(eTileBase* const tile) {
    const bool r = sDefaultWalkable(tile);
    if(!r) return false;
    return tile->terrain() == eTerrain::fertile;
}

void eMoveAroundAction::increment(const int by) {
    mRemTime -= by;
    eMoveAction::increment(by);
}

void eMoveAroundAction::setTime(const int t) {
    mRemTime = t;
}

eCharacterActionState eMoveAroundAction::nextTurn(eOrientation& turn) {
    if(mRemTime <= 0) {
        return eCharacterActionState::finished;
    }
    std::vector<eOrientation> os{eOrientation::topRight,
                                 eOrientation::right,
                                 eOrientation::bottomRight,
                                 eOrientation::bottom,
                                 eOrientation::bottomLeft,
                                 eOrientation::left,
                                 eOrientation::topLeft,
                                 eOrientation::top};
    std::random_shuffle(os.begin(), os.end());
    const auto t = character()->tile();
    if(!t) return eCharacterActionState::failed;
    const int tx = t->x() - mStartTX;
    const int ty = t->y() - mStartTY;
    const int oldDist = std::sqrt(tx*tx + ty*ty);
    for(const auto o : os) {
        const auto tt = t->neighbour(o);
        if(!tt || !walkable(tt)) continue;
        const int ttx = tt->x() - mStartTX;
        const int tty = tt->y() - mStartTY;
        const int dist = std::sqrt(ttx*ttx + tty*tty);
        if(dist >= mMaxDist && dist > oldDist) continue;
        turn = o;
        return eCharacterActionState::running;
    }
    return eCharacterActionState::failed;
}
