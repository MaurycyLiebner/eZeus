#include "egiftfromevent.h"

#include "engine/egameboard.h"
#include "elanguage.h"
#include "estringhelpers.h"
#include "engine/eeventdata.h"
#include "engine/eevent.h"

eGiftFromEvent::eGiftFromEvent(const eGameEventBranch branch) :
    eResourceGrantedEventBase(
        eEvent::giftCashAccepted,
        eEvent::giftAccepted,
        eEvent::giftPostponed,
        eEvent::giftRefused,
        eEvent::giftForfeited,
        eEvent::giftGranted,
        eEvent::giftLastChance,
        eEvent::giftInsufficientSpace,
        eEvent::giftPartialSpace,
        eGameEventType::giftFrom, branch) {}

std::string eGiftFromEvent::longName() const {
    auto tmpl = eLanguage::text("gift_of_from");
    const auto resName = eResourceTypeHelpers::typeName(mResource);
    const auto cStr = std::to_string(mCount);
    const auto none = eLanguage::text("none");
    const auto ctstr = mCity ? mCity->name() : none;
    eStringHelpers::replace(tmpl, "%1", cStr + " " + resName);
    eStringHelpers::replace(tmpl, "%2", ctstr);
    return tmpl;
}
