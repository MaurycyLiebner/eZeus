#include "esoldier.h"

#include "engine/egameboard.h"

eSoldier::eSoldier(eGameBoard& board,
                   const eCharTexs charTexs,
                   const eCharacterType type) :
    eFightingPatroler(board, charTexs, type) {
    board.registerSoldier(this);
}

eSoldier::~eSoldier() {
    auto& brd = getBoard();
    brd.unregisterSoldier(this);
}

eSoldierAction* eSoldier::soldierAction() const {
    return mAction.get();
}

void eSoldier::setSoldierAction(const stdsptr<eSoldierAction>& a) {
    mAction = a;
}
