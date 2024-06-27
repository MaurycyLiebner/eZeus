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
    int a = city->armyTarget();
    a = std::clamp(a + by, 1, 5);
    city->setArmyTarget(a);
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
