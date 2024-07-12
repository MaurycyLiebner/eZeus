#include "erivalarmyawayevent.h"

#include "engine/egameboard.h"
#include "engine/eeventdata.h"
#include "engine/eevent.h"
#include "elanguage.h"

eRivalArmyAwayEvent::eRivalArmyAwayEvent(const eGameEventBranch branch) :
    eGameEvent(eGameEventType::rivalArmyAway, branch) {}

void eRivalArmyAwayEvent::trigger() {
    if(!mCity) return;
    const auto board = gameBoard();
    if(!board) return;
    eEventData ed;
    ed.fCity = mCity;
    if(mEnd) {
        const int t = mCity->troops();
        mCity->setTroops(mTroopsTaken + t);
    } else {
        const int t = mCity->troops();
        mTroopsTaken = 0.6*t;
        mCity->setTroops(t - mTroopsTaken);

        const auto e = e::make_shared<eRivalArmyAwayEvent>(
                           eGameEventBranch::child);
        e->setCity(mCity);
        e->setEnd(true);
        e->setDuration(mDuration);
        const auto date = board->date();
        e->initializeDate(date + std::round(mDuration*30.5));
        addConsequence(e);
        board->event(eEvent::rivalArmyAway, ed);
    }
}

std::string eRivalArmyAwayEvent::longName() const {
    return eLanguage::text("rival_army_away_long_name");
}

void eRivalArmyAwayEvent::write(eWriteStream& dst) const {
    eGameEvent::write(dst);
    dst.writeCity(mCity.get());
    dst << mDuration;
    dst << mEnd;
}

void eRivalArmyAwayEvent::read(eReadStream& src) {
    eGameEvent::read(src);
    src.readCity(worldBoard(), [this](const stdsptr<eWorldCity>& c) {
        mCity = c;
    });
    src >> mDuration;
    src >> mEnd;
}
