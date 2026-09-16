#include "emakerequestevent.h"

#include "engine/egameboard.h"
#include "elanguage.h"
#include "estringhelpers.h"
#include "engine/eeventdata.h"
#include "engine/eevent.h"
#include "engine/egifthelpers.h"

eMakeRequestEvent::eMakeRequestEvent(
        const eCityId cid,
        const eGameEventBranch branch,
        eGameBoard& board) :
    eResourceGrantedEventBase(cid,
                              eEvent::requestAccepted,
                              eEvent::requestAccepted,
                              eEvent::requestPostponed,
                              eEvent::requestRefused,
                              eEvent::requestForfeited,
                              eEvent::requestGranted,
                              eEvent::requestLastChance,
                              eEvent::requestInsufficientSpace,
                              eEvent::requestPartialSpace,
                              eGameEventType::makeRequest,
                              branch, board) {}

void eMakeRequestEvent::initialize(
        const bool postpone,
        const eResourceType res,
        const stdsptr<eWorldCity> &c) {
    mPostpone = postpone;
    setResourceType(0, res);
    mResource = res;
    mCity = c;
    mCount = 2*eGiftHelpers::giftCount(mResource);
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
