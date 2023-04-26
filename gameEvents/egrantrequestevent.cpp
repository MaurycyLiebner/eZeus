#include "egrantrequestevent.h"

#include "engine/egameboard.h"
#include "elanguage.h"
#include "estringhelpers.h"

eGrantRequestEvent::eGrantRequestEvent(
        eGameBoard& board) :
    eGameEvent(eGameEventType::grantRequest, board) {}

void eGrantRequestEvent::initialize(
        const bool postpone,
        const eResourceType res,
        const stdsptr<eWorldCity> &c) {
    mPostpone = postpone;
    mResource = res;
    mCity = c;
}

void eGrantRequestEvent::trigger() {
    auto& board = getBoard();
    board.grantRequest(mCity, mResource, mPostpone);
}

std::string eGrantRequestEvent::longName() const {
    auto tmpl = eLanguage::text("make_request");
    const auto resName = eResourceTypeHelpers::typeName(mResource);
    eStringHelpers::replace(tmpl, "%1", resName);
    eStringHelpers::replace(tmpl, "%2", mCity->name());
    return tmpl;
}

void eGrantRequestEvent::write(eWriteStream& dst) const {
    eGameEvent::write(dst);
    dst << mPostpone;
    dst << mResource;
    dst.writeCity(mCity.get());
}

void eGrantRequestEvent::read(eReadStream& src) {
    eGameEvent::read(src);
    src >> mPostpone;
    src >> mResource;
    src.readCity(&getBoard(), [this](const stdsptr<eWorldCity>& c) {
        mCity = c;
    });
}
