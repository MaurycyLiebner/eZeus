#include "egiftevent.h"

#include "engine/egameboard.h"

eGiftEvent::eGiftEvent(eGameBoard& board) :
    eGameEvent(eGameEventType::gift, board) {}

void eGiftEvent::initialize(const stdsptr<eWorldCity>& c,
                            const eResourceType type,
                            const int count) {
    mCity = c;
    mResource = type;
    mCount = count;
}

void eGiftEvent::trigger() {
    auto& board = getBoard();
    board.giftReceived(mCity, mResource, mCount);
}

void eGiftEvent::write(eWriteStream& dst) const {
    eGameEvent::write(dst);
    dst << mCount;
    dst << mResource;
    dst.writeCity(mCity.get());
}

void eGiftEvent::read(eReadStream& src) {
    eGameEvent::read(src);
    src >> mCount;
    src >> mResource;
    src.readCity(&getBoard(), [this](const stdsptr<eWorldCity>& c) {
        mCity = c;
    });
}
