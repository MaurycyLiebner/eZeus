#include "earmyeventbase.h"

#include "engine/egameboard.h"

eArmyEventBase::eArmyEventBase(const eGameEventType type,
                               const eGameEventBranch branch,
                               eGameBoard* const board) :
    eGameEvent(type, branch) {
    setGameBoard(board);
    board->addArmyEvent(this);
}

eArmyEventBase::~eArmyEventBase() {
    removeArmyEvent();
}

void eArmyEventBase::removeArmyEvent() {
    const auto board = gameBoard();
    if(!board) return;
    board->removeArmyEvent(this);
}

void eArmyEventBase::write(eWriteStream& dst) const {
    eGameEvent::write(dst);
    mForces.write(dst);
    dst.writeCity(mCity.get());
}

void eArmyEventBase::read(eReadStream& src) {
    eGameEvent::read(src);
    const auto board = gameBoard();
    const auto wboard = worldBoard();
    mForces.read(*board, *wboard, src);
    src.readCity(wboard, [this](const stdsptr<eWorldCity>& c) {
        mCity = c;
    });
}
