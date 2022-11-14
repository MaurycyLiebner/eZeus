#include "emovearoundaction.h"

#include "characters/echaracter.h"

eMoveAroundAction::eMoveAroundAction(eCharacter* const c,
                                     const int startX, const int startY,
                                     const stdsptr<eWalkableObject>& walkable) :
    eMoveAction(c, walkable) {
    mStartTX = startX;
    mStartTY = startY;
}

void eMoveAroundAction::increment(const int by) {
    mRemTime -= by;
    eMoveAction::increment(by);
}

void eMoveAroundAction::setTime(const int t) {
    mRemTime = t;
}

void eMoveAroundAction::setMaxDistance(const int md) {
    mMaxDist = md;
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
