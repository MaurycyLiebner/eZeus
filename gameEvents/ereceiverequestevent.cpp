#include "ereceiverequestevent.h"

#include "engine/egameboard.h"
#include "elanguage.h"
#include "estringhelpers.h"

eReceiveRequestEvent::eReceiveRequestEvent(
        eGameBoard& board) :
    eGameEvent(eGameEventType::receiveRequest, board) {}

void eReceiveRequestEvent::initialize(
        const int postpone,
        const eResourceType res,
        const int count,
        const stdsptr<eWorldCity> &c) {
    mPostpone = postpone;
    mResource = res;
    mCount = count;
    mCity = c;
}

void eReceiveRequestEvent::trigger() {
    auto& board = getBoard();
    board.receiveRequest(mCity, mResource, mCount, mPostpone);
}

std::string eReceiveRequestEvent::longName() const {
    auto tmpl = eLanguage::text("receive_request");
    const auto resName = eResourceTypeHelpers::typeName(mResource);
    const auto cStr = std::to_string(mCount);
    eStringHelpers::replace(tmpl, "%1", cStr + " " + resName);
    const auto none = eLanguage::text("none");
    const auto ctstr = mCity ? mCity->name() : none;
    eStringHelpers::replace(tmpl, "%2", ctstr);
    return tmpl;
}

void eReceiveRequestEvent::write(eWriteStream& dst) const {
    eGameEvent::write(dst);
    dst << mPostpone;
    dst << mResource;
    dst << mCount;
    dst.writeCity(mCity.get());
}

void eReceiveRequestEvent::read(eReadStream& src) {
    eGameEvent::read(src);
    src >> mPostpone;
    src >> mResource;
    src >> mCount;
    src.readCity(&getBoard(), [this](const stdsptr<eWorldCity>& c) {
        mCity = c;
    });
}

void eReceiveRequestEvent::setCity(const stdsptr<eWorldCity>& c) {
    mCity = c;
}

void eReceiveRequestEvent::setResourceType(const eResourceType type) {
    mResource = type;
}

void eReceiveRequestEvent::setResourceCount(const int c) {
    mCount = c;
}
