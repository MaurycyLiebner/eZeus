#include "erequeststrikeevent.h"


#include "engine/egameboard.h"
#include "engine/eeventdata.h"
#include "engine/eevent.h"
#include "elanguage.h"

eRequestStrikeEvent::eRequestStrikeEvent(const eGameEventBranch branch) :
    eGameEvent(eGameEventType::requestStrike, branch) {}

const double gStrikeFrac = 0.67;

void eRequestStrikeEvent::trigger() {
    if(!mCity || !mRivalCity) return;
    const auto board = gameBoard();
    if(!board) return;
    eEventData ed;
    ed.fCity = mCity;
    ed.fRivalCity = mRivalCity;

   const auto date = board->date();

    if(mEnd) {
        const int str = gStrikeFrac*mCity->troops();
        const int rstr = mRivalCity->troops();

        if(str > 1.5*rstr) {
            mRivalCity->setRelationship(eForeignCityRelationship::vassal);
            board->event(eEvent::strikeSuccessful, ed);
        } else {
            board->event(eEvent::strikeUnsuccessful, ed);
        }
        {
            const int troops = mRivalCity->troops();
            const double killFrac = std::clamp(0.5*str/rstr, 0., 1.);
            mRivalCity->setTroops((1 - killFrac)*troops);
        }

        {
            const int troops = mCity->troops();
            const double killFrac = std::clamp(0.5*rstr/str, 0., 1.);
            mCity->setTroops((1 - gStrikeFrac*killFrac)*troops);
        }
    } else {
        const auto e = e::make_shared<eRequestStrikeEvent>(
                           eGameEventBranch::child);
        e->setCity(mCity);
        e->setRivalCity(mRivalCity);
        e->setEnd(true);
        e->initializeDate(date + 100);
        addConsequence(e);
        board->event(eEvent::strikeDeparture, ed);
    }
}

std::string eRequestStrikeEvent::longName() const {
    return eLanguage::text("request_strike_long_name");
}

void eRequestStrikeEvent::write(eWriteStream& dst) const {
    eGameEvent::write(dst);
    dst.writeCity(mCity.get());
    dst.writeCity(mRivalCity.get());
    dst << mEnd;
}

void eRequestStrikeEvent::read(eReadStream& src) {
    eGameEvent::read(src);
    src.readCity(worldBoard(), [this](const stdsptr<eWorldCity>& c) {
        mCity = c;
    });
    src.readCity(worldBoard(), [this](const stdsptr<eWorldCity>& c) {
        mRivalCity = c;
    });
    src >> mEnd;
}
