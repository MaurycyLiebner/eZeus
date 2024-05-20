#include "eplayerconquesteventbase.h"

#include "engine/egameboard.h"
#include "earmyreturnevent.h"

void ePlayerConquestEventBase::addAres() {
    mForces.fAres = true;
}

void ePlayerConquestEventBase::postTrigger() {
    auto& board = getBoard();
    const auto e = e::make_shared<eArmyReturnEvent>(
                       eGameEventBranch::child, board);
    const auto boardDate = board.date();
    const int period = ePlayerConquestEventBase::sWaitTime;
    const auto date = boardDate + period;
    e->initializeDate(date, period, 1);
    e->initialize(mForces, mCity);
    addConsequence(e);
}
