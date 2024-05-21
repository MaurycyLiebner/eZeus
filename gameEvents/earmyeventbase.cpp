#include "earmyeventbase.h"

#include "engine/egameboard.h"

eArmyEventBase::eArmyEventBase(const eGameEventType type,
                               const eGameEventBranch branch,
                               eGameBoard& board) :
    eGameEvent(type, branch, board) {
    board.addArmyEvent(this);
}

eArmyEventBase::~eArmyEventBase() {
    removeArmyEvent();
}

void eArmyEventBase::removeArmyEvent() {
    auto& board = getBoard();
    board.removeArmyEvent(this);
}
