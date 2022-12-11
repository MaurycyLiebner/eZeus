#include "epaytributeevent.h"

#include "engine/egameboard.h"

ePayTributeEvent::ePayTributeEvent(eGameBoard& board) :
    eGameEvent(eGameEventType::payTribute, board) {}

void ePayTributeEvent::initialize(const stdsptr<eWorldCity>& c) {
    mCity = c;
}

void ePayTributeEvent::trigger() {
    auto& board = getBoard();
    board.payTribute(mCity, false);
}

void ePayTributeEvent::write(eWriteStream& dst) const {
    eGameEvent::write(dst);
    dst.writeCity(mCity.get());
}

void ePayTributeEvent::read(eReadStream& src) {
    eGameEvent::read(src);
    src.readCity(&getBoard(), [this](const stdsptr<eWorldCity>& c) {
        mCity = c;
    });
}
