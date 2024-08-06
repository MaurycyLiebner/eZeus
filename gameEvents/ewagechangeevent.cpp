#include "ewagechangeevent.h"

#include "engine/egameboard.h"
#include "engine/eeventdata.h"
#include "engine/eevent.h"
#include "estringhelpers.h"
#include "elanguage.h"

eWageChangeEvent::eWageChangeEvent(const eGameEventBranch branch) :
    eGameEvent(eGameEventType::wageChange, branch) {}

void eWageChangeEvent::write(eWriteStream& dst) const {
    eGameEvent::write(dst);
    dst << mBy;
}

void eWageChangeEvent::read(eReadStream& src) {
    eGameEvent::read(src);
    src >> mBy;
}

void eWageChangeEvent::trigger() {
    const auto board = gameBoard();
    if(!board) return;
    board->changeWage(mBy);
    eEventData ed;
    const auto e = mBy > 0 ? eEvent::wageIncrease :
                             eEvent::wageDecrease;
    board->event(e, ed);
}

std::string eWageChangeEvent::longName() const {
    return eLanguage::text("wage_change");
}
