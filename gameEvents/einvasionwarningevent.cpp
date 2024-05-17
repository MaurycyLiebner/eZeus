#include "einvasionwarningevent.h"

#include "elanguage.h"
#include "estringhelpers.h"
#include "engine/eworldcity.h"
#include "engine/egameboard.h"
#include "engine/eevent.h"
#include "engine/eeventdata.h"

eInvasionWarningEvent::eInvasionWarningEvent(
        const eGameEventBranch branch, eGameBoard& board) :
    eGameEvent(eGameEventType::invasionWarning, branch, board) {}

void eInvasionWarningEvent::initialize(
        const eInvasionWarningType type,
        const stdsptr<eWorldCity>& city) {
    mType = type;
    mCity = city;
}

void eInvasionWarningEvent::trigger() {
    auto& board = getBoard();
    eEventData ed;
    ed.fCity = mCity;
    switch(mType) {
    case eInvasionWarningType::warning36: {
        board.event(eEvent::invasion36, ed);
    } break;
    case eInvasionWarningType::warning24: {
        board.event(eEvent::invasion24, ed);
    } break;
    case eInvasionWarningType::warning12: {
        board.event(eEvent::invasion12, ed);
    } break;
    case eInvasionWarningType::warning6: {
        board.event(eEvent::invasion6, ed);
    } break;
    case eInvasionWarningType::warning1: {
        board.event(eEvent::invasion1, ed);
    } break;
    }
}

std::string eInvasionWarningEvent::longName() const {
    auto tmpl = eLanguage::text("invasion_by");
    const auto none = eLanguage::text("none");
    const auto cstr = mCity ? mCity->name() : none;
    eStringHelpers::replace(tmpl, "%1", cstr);
    return tmpl;
}

void eInvasionWarningEvent::write(eWriteStream& dst) const {
    eGameEvent::write(dst);
    dst << mType;
    dst.writeCity(mCity.get());
}

void eInvasionWarningEvent::read(eReadStream& src) {
    eGameEvent::read(src);
    src >> mType;
    src.readCity(&getBoard(), [this](const stdsptr<eWorldCity>& c) {
        mCity = c;
    });
}

stdsptr<eGameEvent> eInvasionWarningEvent::makeCopy(
        const std::string& reason) const {
    const auto c = e::make_shared<eInvasionWarningEvent>(
                       branch(), getBoard());
    c->setReason(reason);
    c->mType = mType;
    c->mCity = mCity;
    return c;
}

void eInvasionWarningEvent::setCity(const stdsptr<eWorldCity>& c) {
    mCity = c;
}
