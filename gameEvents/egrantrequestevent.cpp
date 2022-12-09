#include "egrantrequestevent.h"

#include "engine/egameboard.h"

eGrantRequestEvent::eGrantRequestEvent(const stdsptr<eWorldCity>& c,
                                       const eResourceType type,
                                       eGameBoard& board) :
    eGameEvent(eGameEventType::grantRequest, board),
    mType(type), mCity(c) {}

void eGrantRequestEvent::trigger() {
    auto& board = getBoard();
    board.grantRequest(mCity, mType);
}

void eGrantRequestEvent::write(eWriteStream& dst) const {
    eGameEvent::write(dst);
    dst.writeCity(mCity.get());
    dst << mType;
}

void eGrantRequestEvent::read(eReadStream& src) {
    eGameEvent::read(src);
    src.readCity(&getBoard(), [this](const stdsptr<eWorldCity>& c) {
        mCity = c;
    });
    src >> mType;
}
