#include "emovearoundaction.h"

#include "characters/echaracter.h"

eMoveAroundAction::eMoveAroundAction(eCharacter* const c) :
    eMoveAction(c, [](eTile* const) { return true; }) {
    for(int i = 0; i < 100; i++) {
        const int oid = rand() % 8;
        const auto o = static_cast<eOrientation>(oid);
        mTurns.push_back(o);
    }
}

bool eMoveAroundAction::nextTurn(eOrientation& turn) {
    if(mTurns.empty()) return false;
    turn = mTurns.back();
    mTurns.pop_back();

    const auto t = character()->tile();
    const auto tt = t->neighbour(turn);
    if(!tt) return nextTurn(turn);
    return true;
}
