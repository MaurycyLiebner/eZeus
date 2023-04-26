#include "egrantgeneralrequestevent.h"

#include "engine/egameboard.h"
#include "elanguage.h"
#include "estringhelpers.h"

eGrantGeneralRequestEvent::eGrantGeneralRequestEvent(
        eGameBoard& board) :
    eGameEvent(eGameEventType::grantRequest, board) {}

void eGrantGeneralRequestEvent::initialize(
        const int postpone,
        const eResourceType res,
        const int count,
        const stdsptr<eWorldCity> &c) {
    mPostpone = postpone;
    mResource = res;
    mCount = count;
    mCity = c;
}

void eGrantGeneralRequestEvent::trigger() {
    auto& board = getBoard();
    board.grantGeneralRequest(mCity, mResource, mCount, mPostpone);
}

std::string eGrantGeneralRequestEvent::longName() const {
    auto tmpl = eLanguage::text("receive_request");
    const auto resName = eResourceTypeHelpers::typeName(mResource);
    const auto cStr = std::to_string(mCount);
    eStringHelpers::replace(tmpl, "%1", cStr + " " + resName);
    eStringHelpers::replace(tmpl, "%2", mCity->name());
    return tmpl;
}

void eGrantGeneralRequestEvent::write(eWriteStream& dst) const {
    eGameEvent::write(dst);
    dst << mPostpone;
    dst << mResource;
    dst << mCount;
    dst.writeCity(mCity.get());
}

void eGrantGeneralRequestEvent::read(eReadStream& src) {
    eGameEvent::read(src);
    src >> mPostpone;
    src >> mResource;
    src >> mCount;
    src.readCity(&getBoard(), [this](const stdsptr<eWorldCity>& c) {
        mCity = c;
    });
}
