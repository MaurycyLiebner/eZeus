#include "emakerequestevent.h"

#include "engine/egameboard.h"
#include "elanguage.h"
#include "estringhelpers.h"

eMakeRequestEvent::eMakeRequestEvent(
        eGameBoard& board) :
    eGameEvent(eGameEventType::makeRequest, board) {}

void eMakeRequestEvent::initialize(
        const bool postpone,
        const eResourceType res,
        const stdsptr<eWorldCity> &c) {
    mPostpone = postpone;
    mResource = res;
    mCity = c;
}

void eMakeRequestEvent::trigger() {
    auto& board = getBoard();
    board.makeRequest(mCity, mResource, mPostpone);
}

std::string eMakeRequestEvent::longName() const {
    auto tmpl = eLanguage::text("make_request");
    const auto resName = eResourceTypeHelpers::typeName(mResource);
    eStringHelpers::replace(tmpl, "%1", resName);
    const auto none = eLanguage::text("none");
    const auto ctstr = mCity ? mCity->name() : none;
    eStringHelpers::replace(tmpl, "%2", ctstr);
    return tmpl;
}

void eMakeRequestEvent::write(eWriteStream& dst) const {
    eGameEvent::write(dst);
    dst << mPostpone;
    dst << mResource;
    dst.writeCity(mCity.get());
}

void eMakeRequestEvent::read(eReadStream& src) {
    eGameEvent::read(src);
    src >> mPostpone;
    src >> mResource;
    src.readCity(&getBoard(), [this](const stdsptr<eWorldCity>& c) {
        mCity = c;
    });
}

void eMakeRequestEvent::setCity(const stdsptr<eWorldCity>& c) {
    mCity = c;
}

void eMakeRequestEvent::setResourceType(const eResourceType type) {
    mResource = type;
}
