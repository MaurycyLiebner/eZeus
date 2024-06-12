#include "emilitarychangeevent.h"

#include "engine/egameboard.h"
#include "engine/eeventdata.h"
#include "engine/eevent.h"
#include "elanguage.h"

eMilitaryChangeEvent::eMilitaryChangeEvent(const eGameEventBranch branch) :
    eEconomicMilitaryChangeEventBase(
        eGameEventType::militaryChange, branch) {}

void eMilitaryChangeEvent::trigger() {
    const auto city = this->city();
    const int by = this->by();
    if(!city || by == 0) return;
    int a = city->army();
    a = std::clamp(a + by, 1, 5);
    city->setArmy(a);
    const auto board = gameBoard();
    if(!board) return;
    eEventData ed;
    ed.fCity = city;
    if(by > 0) board->event(eEvent::militaryBuildup, ed);
    else board->event(eEvent::militaryDecline, ed);
}

std::string eMilitaryChangeEvent::longName() const {
    return eLanguage::text("military_change_long_name");
}

stdsptr<eGameEvent> eMilitaryChangeEvent::makeCopy(const std::string& reason) const {
    const auto c = e::make_shared<eMilitaryChangeEvent>(branch());
    c->setGameBoard(gameBoard());
    c->setWorldBoard(worldBoard());
    c->setBy(by());
    c->setCity(city());
    c->setReason(reason);
    return c;
}
