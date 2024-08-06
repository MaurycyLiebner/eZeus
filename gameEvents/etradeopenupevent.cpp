#include "etradeopenupevent.h"

#include "engine/egameboard.h"
#include "engine/eeventdata.h"
#include "engine/eevent.h"
#include "estringhelpers.h"
#include "elanguage.h"

eTradeOpenUpEvent::eTradeOpenUpEvent(const eGameEventBranch branch) :
    eBasicCityEvent(eGameEventType::tradeOpensUp, branch) {}

void eTradeOpenUpEvent::trigger() {
    const auto city = this->city();
    if(!city) return;
    city->setTradeShutdown(false);
    const auto board = gameBoard();
    if(!board) return;
    eEventData ed;
    ed.fCity = city;
    board->event(eEvent::tradeOpensUp, ed);
}

std::string eTradeOpenUpEvent::longName() const {
    auto tmpl = eLanguage::text("trade_openup_long_name");
    const auto none = eLanguage::text("none");
    const auto city = this->city();
    const auto ctstr = city ? city->name() : none;
    eStringHelpers::replace(tmpl, "%1", ctstr);
    return tmpl;
}
