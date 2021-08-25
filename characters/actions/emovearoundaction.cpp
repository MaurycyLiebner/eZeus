#include "emovearoundaction.h"

#include "characters/echaracter.h"

eMoveAroundAction::eMoveAroundAction(eCharacter* const c,
                                     const eAction& failAction,
                                     const eAction& finishAction,
                                     const int startX, const int startY) :
    eMoveAction(c,
                [](eTileBase* const t) { return t->walkable(); },
                failAction,
                finishAction) {
    mStartTX = startX;
    mStartTY = startY;
}

eMoveAroundAction::eMoveAroundAction(eCharacter* const c,
                                     const eAction& failAction,
                                     const eAction& finishAction) :
    eMoveAction(c,
                [](eTileBase* const t) { return t->walkable(); },
                failAction,
                finishAction) {
    const auto t = c->tile();
    mStartTX = t->x();
    mStartTY = t->y();
}

void eMoveAroundAction::increment(const int by) {
    mRemTime -= by;
    if(mRemTime <= 0) {
        return setState(eCharacterActionState::finished);
    } else return eMoveAction::increment(by);
}

void eMoveAroundAction::setTime(const int t) {
    mRemTime = t;
}

eCharacterActionState eMoveAroundAction::nextTurn(
        eOrientation& turn,
        const int n, const int i) {
    const int oid = rand() % 8;
    turn = static_cast<eOrientation>(oid);
    const auto t = character()->tile();
    if(!t) return eCharacterActionState::failed;
    const int tx = t->x() - mStartTX;
    const int ty = t->y() - mStartTY;
    const int oldDist = std::sqrt(tx*tx + ty*ty);
    const auto tt = t->neighbour(turn);
    if(!tt || !tt->walkable()) {
        if(i > 16) return eCharacterActionState::failed;
        return nextTurn(turn, n, i + 1);
    }
    const int ttx = tt->x() - mStartTX;
    const int tty = tt->y() - mStartTY;
    const int dist = std::sqrt(ttx*ttx + tty*tty);
    if(dist >= mMaxDist && dist > oldDist && n < 2)
        return nextTurn(turn, n + 1, i);
    return eCharacterActionState::running;
}


eCharacterActionState eMoveAroundAction::nextTurn(eOrientation& turn) {
    return nextTurn(turn, 0, 0);
}
