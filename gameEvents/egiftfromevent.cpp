#include "egiftfromevent.h"

#include "engine/egameboard.h"

eGiftFromEvent::eGiftFromEvent(eGameBoard& board) :
    eGameEvent(eGameEventType::giftFrom, board) {}

void eGiftFromEvent::initialize(
        const bool postpone,
        const eResourceType res,
        const int count,
        const stdsptr<eWorldCity> &c) {
    mPostpone = postpone;
    mResource = res;
    mCount = count;
    mCity = c;
}

void eGiftFromEvent::trigger() {
    auto& board = getBoard();
    board.giftFrom(mCity, mResource, mCount, mPostpone);
}

void eGiftFromEvent::write(eWriteStream& dst) const {
    eGameEvent::write(dst);
    dst << mPostpone;
    dst << mResource;
    dst << mCount;
    dst.writeCity(mCity.get());
}

void eGiftFromEvent::read(eReadStream& src) {
    eGameEvent::read(src);
    src >> mPostpone;
    src >> mResource;
    src >> mCount;
    src.readCity(&getBoard(), [this](const stdsptr<eWorldCity>& c) {
        mCity = c;
    });
}
