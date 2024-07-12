#include "egodtraderesumesevent.h"

#include "engine/egameboard.h"
#include "engine/eeventdata.h"
#include "engine/eevent.h"
#include "elanguage.h"

eGodTradeResumesEvent::eGodTradeResumesEvent(const eGameEventBranch branch) :
    eGameEvent(eGameEventType::godTradeResumes, branch) {}

void eGodTradeResumesEvent::trigger() {
    const auto board = gameBoard();
    if(!board) return;
    if(mGod == eGodType::zeus) {
        board->setLandTradeShutdown(false);
        board->setSeaTradeShutdown(false);
    } else if(mGod == eGodType::poseidon) {
        board->setSeaTradeShutdown(false);
    } else if(mGod == eGodType::hermes) {
        board->setLandTradeShutdown(false);
    }
    eEventData ed;
    ed.fGod = mGod;
    board->event(eEvent::godTradeResumes, ed);
}

std::string eGodTradeResumesEvent::longName() const {
    return eLanguage::text("god_trade_resumes_long_name");
}

void eGodTradeResumesEvent::write(eWriteStream& dst) const {
    eGameEvent::write(dst);
    dst << mGod;
}

void eGodTradeResumesEvent::read(eReadStream& src) {
    eGameEvent::read(src);
    src >> mGod;
}
