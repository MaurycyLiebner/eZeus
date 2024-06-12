#include "eeconomicchangeevent.h"

#include "engine/egameboard.h"
#include "engine/eeventdata.h"
#include "engine/eevent.h"
#include "elanguage.h"

eEconomicChangeEvent::eEconomicChangeEvent(const eGameEventBranch branch) :
    eEconomicMilitaryChangeEventBase(
        eGameEventType::economicChange, branch) {}

void eEconomicChangeEvent::trigger() {
    const auto city = this->city();
    const int by = this->by();
    if(!city || by == 0) return;
    int w = city->wealth();
    w = std::clamp(w + by, 1, 5);
    city->setWealth(w);
    const auto board = gameBoard();
    if(!board) return;
    eEventData ed;
    ed.fCity = city;
    if(by > 0) board->event(eEvent::economicProsperity, ed);
    else board->event(eEvent::economicDecline, ed);
}

std::string eEconomicChangeEvent::longName() const {
    return eLanguage::text("economic_change_long_name");
}

stdsptr<eGameEvent> eEconomicChangeEvent::makeCopy(const std::string& reason) const {
    const auto c = e::make_shared<eEconomicChangeEvent>(branch());
    c->setGameBoard(gameBoard());
    c->setWorldBoard(worldBoard());
    c->setBy(by());
    c->setCity(city());
    c->setReason(reason);
    return c;
}
