#include "eplayerconquesteventbase.h"

#include "engine/egameboard.h"
#include "earmyreturnevent.h"

ePlayerConquestEventBase::ePlayerConquestEventBase(
        const eGameEventType type,
        const eGameEventBranch branch,
        eGameBoard& board) :
    eArmyEventBase(type, branch, board) {
    board.addConquest(this);
}

ePlayerConquestEventBase::~ePlayerConquestEventBase() {
    removeConquestEvent();
}

void ePlayerConquestEventBase::addAres() {
    mForces.fAres = true;
}

void ePlayerConquestEventBase::removeConquestEvent() {
    auto& board = getBoard();
    board.removeConquest(this);
}

void ePlayerConquestEventBase::planArmyReturn() {
    auto& board = getBoard();
    const auto e = e::make_shared<eArmyReturnEvent>(
                       eGameEventBranch::child, board);
    const auto boardDate = board.date();
    const int period = eArmyEventBase::sWaitTime;
    const auto date = boardDate + period;
    e->initializeDate(date, period, 1);
    e->initialize(mForces, mCity);
    addConsequence(e);
}
