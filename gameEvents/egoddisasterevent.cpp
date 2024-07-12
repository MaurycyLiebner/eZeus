#include "egoddisasterevent.h"

#include "engine/egameboard.h"
#include "engine/eeventdata.h"
#include "engine/eevent.h"
#include "elanguage.h"

eGodDisasterEvent::eGodDisasterEvent(const eGameEventBranch branch) :
    eGameEvent(eGameEventType::godDisaster, branch) {}

void eGodDisasterEvent::trigger() {
    if(!mCity) return;
    const auto board = gameBoard();
    if(!board) return;
    eEventData ed;
    ed.fCity = mCity;
    ed.fGod = mGod;
    if(mEnd) {
        mCity->setTradeShutdown(false);
        board->event(eEvent::godDisasterEnds, ed);
    } else {
        mCity->setTradeShutdown(true);
        const auto e = e::make_shared<eGodDisasterEvent>(
                           eGameEventBranch::child);
        e->setGod(mGod);
        e->setCity(mCity);
        e->setEnd(true);
        e->initializeDate(board->date() + mDuration);
        addConsequence(e);
        board->event(eEvent::godDisaster, ed);
    }
}

std::string eGodDisasterEvent::longName() const {
    return eLanguage::text("god_disaster_long_name");
}

void eGodDisasterEvent::write(eWriteStream& dst) const {
    eGameEvent::write(dst);
    dst << mDuration;
    dst << mGod;
    dst << mEnd;
    dst.writeCity(mCity.get());
}

void eGodDisasterEvent::read(eReadStream& src) {
    eGameEvent::read(src);
    src >> mDuration;
    src >> mGod;
    src >> mEnd;
    src.readCity(worldBoard(), [this](const stdsptr<eWorldCity>& c) {
        mCity = c;
    });
}
