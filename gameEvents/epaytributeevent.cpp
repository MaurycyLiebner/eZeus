#include "epaytributeevent.h"

#include "engine/egameboard.h"
#include "elanguage.h"
#include "estringhelpers.h"

ePayTributeEvent::ePayTributeEvent(eGameBoard& board) :
    eGameEvent(eGameEventType::payTribute, board) {}

void ePayTributeEvent::initialize(const stdsptr<eWorldCity>& c) {
    mCity = c;
}

void ePayTributeEvent::trigger() {
    auto& board = getBoard();
    board.tributeFrom(mCity, false);
}

std::string ePayTributeEvent::longName() const {
    auto tmpl = eLanguage::text("receive_tribute_from");
    eStringHelpers::replace(tmpl, "%1", mCity->name());
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
