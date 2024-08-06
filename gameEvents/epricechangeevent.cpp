#include "epricechangeevent.h"

#include "engine/egameboard.h"
#include "engine/eeventdata.h"
#include "engine/eevent.h"
#include "estringhelpers.h"
#include "elanguage.h"

ePriceChangeEvent::ePriceChangeEvent(const eGameEventBranch branch) :
    eGameEvent(eGameEventType::priceChange, branch) {}

void ePriceChangeEvent::write(eWriteStream& dst) const {
    eGameEvent::write(dst);
    dst << mType;
    dst << mBy;
}

void ePriceChangeEvent::read(eReadStream& src) {
    eGameEvent::read(src);
    src >> mType;
    src >> mBy;
}

void ePriceChangeEvent::trigger() {
    const auto board = gameBoard();
    if(!board) return;
    board->incPrice(mType, mBy);
    eEventData ed;
    ed.fResourceType = mType;
    const auto e = mBy > 0 ? eEvent::priceIncrease :
                             eEvent::priceDecrease;
    board->event(e, ed);
}

std::string ePriceChangeEvent::longName() const {
    auto tmpl = eLanguage::text("price_change_long_name");
    const auto resName = eResourceTypeHelpers::typeName(mType);
    eStringHelpers::replace(tmpl, "%1", resName);
    return tmpl;
}
