#include "einvasionwarningevent.h"

#include "elanguage.h"
#include "estringhelpers.h"
#include "engine/eworldcity.h"
#include "engine/egameboard.h"
#include "engine/eevent.h"
#include "engine/eeventdata.h"
#include "einvasionevent.h"

eInvasionWarningEvent::eInvasionWarningEvent(const eGameEventBranch branch) :
    eGameEvent(eGameEventType::invasionWarning, branch) {}

void eInvasionWarningEvent::initialize(
        const eInvasionWarningType type,
        const stdsptr<eWorldCity>& city) {
    mType = type;
    mCity = city;
}

void eInvasionWarningEvent::trigger() {
    const auto board = gameBoard();
    if(!board) return;
    eEventData ed;
    ed.fCity = mCity;
    switch(mType) {
    case eInvasionWarningType::warning36: {
        board->event(eEvent::invasion36, ed);
    } break;
    case eInvasionWarningType::warning24: {
        board->event(eEvent::invasion24, ed);
    } break;
    case eInvasionWarningType::warning12: {
        board->event(eEvent::invasion12, ed);
    } break;
    case eInvasionWarningType::warning6: {
        board->event(eEvent::invasion6, ed);
    } break;
    case eInvasionWarningType::warning1: {
        board->event(eEvent::invasion1, ed);
    } break;
    }

    const auto p = parent();
    if(const auto i = dynamic_cast<eInvasionEvent*>(p)) {
        const bool w = i->warned();
        if(w) return;
        i->setFirstWarning(startDate());
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
    src.readCity(worldBoard(), [this](const stdsptr<eWorldCity>& c) {
        mCity = c;
    });
}

void eInvasionWarningEvent::setCity(const stdsptr<eWorldCity>& c) {
    mCity = c;
}
