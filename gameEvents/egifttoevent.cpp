#include "egifttoevent.h"

#include "engine/egameboard.h"
#include "elanguage.h"
#include "estringhelpers.h"

eGiftToEvent::eGiftToEvent(const eGameEventBranch branch,
                           eGameBoard& board) :
    eGameEvent(eGameEventType::giftTo, branch, board) {}

void eGiftToEvent::initialize(const stdsptr<eWorldCity>& c,
                              const eResourceType type,
                              const int count) {
    mCity = c;
    mResource = type;
    mCount = count;
}

void eGiftToEvent::trigger() {
    auto& board = getBoard();
    board.giftToReceived(mCity, mResource, mCount);
}

std::string eGiftToEvent::longName() const {
    auto tmpl = eLanguage::text("gift_of_to");
    const auto resName = eResourceTypeHelpers::typeName(mResource);
    const auto cStr = std::to_string(mCount);
    eStringHelpers::replace(tmpl, "%1", cStr + " " + resName);
    const auto none = eLanguage::text("none");
    const auto ctstr = mCity ? mCity->name() : none;
    eStringHelpers::replace(tmpl, "%2", ctstr);
    return tmpl;
}

void eGiftToEvent::write(eWriteStream& dst) const {
    eGameEvent::write(dst);
    dst << mCount;
    dst << mResource;
    dst.writeCity(mCity.get());
}

void eGiftToEvent::read(eReadStream& src) {
    eGameEvent::read(src);
    src >> mCount;
    src >> mResource;
    src.readCity(&getBoard(), [this](const stdsptr<eWorldCity>& c) {
        mCity = c;
    });
}

stdsptr<eGameEvent> eGiftToEvent::makeCopy(const std::string& reason) const {
    const auto c = e::make_shared<eGiftToEvent>(branch(), getBoard());
    c->setReason(reason);
    c->initialize(mCity, mResource, mCount);
    return c;
}
