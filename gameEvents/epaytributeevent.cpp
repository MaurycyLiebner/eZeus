#include "epaytributeevent.h"

#include "engine/egameboard.h"
#include "elanguage.h"
#include "estringhelpers.h"

ePayTributeEvent::ePayTributeEvent(const eGameEventBranch branch,
                                   eGameBoard& board) :
    eGameEvent(eGameEventType::payTribute, branch, board) {}

void ePayTributeEvent::initialize(const stdsptr<eWorldCity>& c) {
    mCity = c;
}

void ePayTributeEvent::trigger() {
    if(!mCity) return;
    auto& board = getBoard();
    board.tributeFrom(mCity, false);
}

std::string ePayTributeEvent::longName() const {
    auto tmpl = eLanguage::text("receive_tribute_from");
    const auto none = eLanguage::text("none");
    const auto ctstr = mCity ? mCity->name() : none;
    eStringHelpers::replace(tmpl, "%1", ctstr);
    return tmpl;
}

void ePayTributeEvent::write(eWriteStream& dst) const {
    eGameEvent::write(dst);
    dst.writeCity(mCity.get());
}

void ePayTributeEvent::read(eReadStream& src) {
    eGameEvent::read(src);
    src.readCity(&getBoard(), [this](const stdsptr<eWorldCity>& c) {
        mCity = c;
    });
}

stdsptr<eGameEvent> ePayTributeEvent::makeCopy(const std::string& reason) const {
    const auto c = e::make_shared<ePayTributeEvent>(branch(), getBoard());
    c->setReason(reason);
    c->initialize(mCity);
    return c;
}
