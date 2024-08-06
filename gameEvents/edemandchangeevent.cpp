#include "edemandchangeevent.h"

#include "engine/egameboard.h"
#include "engine/eeventdata.h"
#include "engine/eevent.h"
#include "estringhelpers.h"
#include "elanguage.h"

eDemandChangeEvent::eDemandChangeEvent(const eGameEventBranch branch) :
    eSupplyDemandChangeEvent(eGameEventType::demandChange, branch) {}

void eDemandChangeEvent::trigger() {
    const auto city = this->city();
    if(!city) return;
    const auto type = this->type();
    const int by = this->by();
    auto& buys = city->buys();
    for(auto& b : buys) {
        if(b.fType != type) continue;
        b.fMax += by;
        break;
    }
    const auto board = gameBoard();
    if(!board) return;
    eEventData ed;
    ed.fCity = city;
    ed.fResourceType = type;
    const auto e = by > 0 ? eEvent::demandIncrease :
                            eEvent::demandDecrease;
    board->event(e, ed);
}

std::string eDemandChangeEvent::longName() const {
    auto tmpl = eLanguage::text("demand_change_long_name");
    const auto none = eLanguage::text("none");
    const auto city = this->city();
    const auto ctstr = city ? city->name() : none;
    eStringHelpers::replace(tmpl, "%1", ctstr);
    return tmpl;
}
