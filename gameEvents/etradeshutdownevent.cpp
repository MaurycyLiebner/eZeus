#include "etradeshutdownevent.h"

#include "engine/egameboard.h"
#include "engine/eeventdata.h"
#include "engine/eevent.h"
#include "estringhelpers.h"
#include "elanguage.h"

eTradeShutDownEvent::eTradeShutDownEvent(const eGameEventBranch branch) :
    eBasicCityEvent(eGameEventType::tradeShutdowns, branch) {}

void eTradeShutDownEvent::trigger() {
    const auto city = this->city();
    if(!city) return;
    city->setTradeShutdown(true);
    const auto board = gameBoard();
    if(!board) return;
    eEventData ed;
    ed.fCity = city;
    board->event(eEvent::tradeShutdowns, ed);
}

std::string eTradeShutDownEvent::longName() const {
    auto tmpl = eLanguage::text("trade_shutdown_long_name");
    const auto none = eLanguage::text("none");
    const auto city = this->city();
    const auto ctstr = city ? city->name() : none;
    eStringHelpers::replace(tmpl, "%1", ctstr);
    return tmpl;
}
