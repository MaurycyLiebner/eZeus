#include "emovearoundaction.h"

#include "characters/echaracter.h"

eMoveAroundAction::eMoveAroundAction(eCharacter* const c) :
    eMoveAction(c,
                [](eTile* const) { return true; },
                []() {},
                []() {}) {
    for(int i = 0; i < 100; i++) {
        const int oid = rand() % 8;
        const auto o = static_cast<eOrientation>(oid);
        mTurns.push_back(o);
    }
}

eCharacterActionState eMoveAroundAction::nextTurn(eOrientation& turn) {
    if(mTurns.empty()) return eCharacterActionState::finished;
    turn = mTurns.back();
    mTurns.pop_back();

    const auto t = character()->tile();
    const auto tt = t->neighbour(turn);
    if(!tt) return nextTurn(turn);
    return eCharacterActionState::running;
}
