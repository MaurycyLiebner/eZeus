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

void eArmyEventBase::write(eWriteStream& dst) const {
    eGameEvent::write(dst);
    mForces.write(dst);
    dst.writeCity(mCity.get());
}

void eArmyEventBase::read(eReadStream& src) {
    eGameEvent::read(src);
    auto& board = getBoard();
    mForces.read(board, src);
    src.readCity(&board, [this](const stdsptr<eWorldCity>& c) {
        mCity = c;
    });
}
