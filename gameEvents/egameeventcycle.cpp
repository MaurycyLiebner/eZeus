#include "egameeventcycle.h"

eGameEventCycle::eGameEventCycle(const stdsptr<eGameEvent>& event,
                                 const eDate& startDate,
                                 const int cycleDays,
                                 const int nRuns,
                                 eGameBoard& board) :
    eObject(board),
    mEvent(event),
    mStartDate(startDate),
    mCycleDays(cycleDays),
    mTotNRuns(nRuns),
    mRemNRuns(nRuns),
    mNextDate(startDate) {}

eGameEventCycle::eGameEventCycle(const stdsptr<eGameEvent>& event,
                                 const eDate& date, eGameBoard& board) :
    eGameEventCycle(event, date, 0, 1, board) {}

eGameEventCycle::eGameEventCycle(eGameBoard& board) :
    eObject(board) {}

std::string eGameEventCycle::longName() const {
    const auto dateStr = mStartDate.shortString();
    const auto eventName = mEvent->longName();
    return dateStr + " " + eventName;
}

void eGameEventCycle::setStartDate(const eDate& d) {
    mStartDate = d;
}

void eGameEventCycle::handleNewDate(const eDate& date) {
    if(finished()) return;
    if(date > mNextDate) {
        trigger();
        mRemNRuns--;
        mNextDate += mCycleDays;
    }
}

void eGameEventCycle::rewind(const eDate& date) {
    mNextDate = mStartDate;
    mRemNRuns = mTotNRuns;
    if(mCycleDays <= 0) {
        if(date > mStartDate) mRemNRuns--;
        return;
    }
    while(date > mNextDate) {
        mRemNRuns--;
        if(mRemNRuns <= 0) break;
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
    mStartDate.write(dst);
    dst << mCycleDays;
    dst << mTotNRuns;
    dst << mRemNRuns;
}

void eGameEventCycle::read(eReadStream& src) {
    eGameEventType type;
    src >> type;
    mEvent = eGameEvent::sCreate(type, getBoard());
    mEvent->read(src);
    mNextDate.read(src);
    mStartDate.read(src);
    src >> mCycleDays;
    src >> mTotNRuns;
    src >> mRemNRuns;
}
