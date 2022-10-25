#include "egameeventcycle.h"

eGameEventCycle::eGameEventCycle(const stdsptr<eGameEvent>& event,
                                 const eDate& startDate,
                                 const int cycleDays,
                                 const int nRuns,
                                 eGameBoard& board) :
    eObject(board),
    mEvent(event),
    mNextDate(startDate),
    mCycleDays(cycleDays),
    mNRuns(nRuns) {}

eGameEventCycle::eGameEventCycle(const stdsptr<eGameEvent>& event,
                                 const eDate& date, eGameBoard& board) :
    eGameEventCycle(event, date, 0, 1, board) {}

eGameEventCycle::eGameEventCycle(eGameBoard& board) :
    eObject(board) {}

void eGameEventCycle::handleNewDate(const eDate& date) {
    if(finished()) return;
    if(date > mNextDate) {
        trigger();
        mNRuns--;
        mNextDate += mCycleDays;
    }
}

void eGameEventCycle::trigger() {
    mEvent->trigger();
}

void eGameEventCycle::write(eWriteStream& dst) const {
    dst << mEvent->type();
    mEvent->write(dst);
    mNextDate.write(dst);
    dst << mCycleDays;
    dst << mNRuns;
}

void eGameEventCycle::read(eReadStream& src) {
    eGameEventType type;
    src >> type;
    mEvent = eGameEvent::sCreate(type, getBoard());
    mEvent->read(src);
    mNextDate.read(src);
    src >> mCycleDays;
    src >> mNRuns;
}
