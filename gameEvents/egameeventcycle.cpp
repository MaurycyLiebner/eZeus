#include "egameeventcycle.h"

#include "engine/egameboard.h"

eGameEventCycle::eGameEventCycle(const stdsptr<eGameEvent>& event,
                                 const eDate& startDate,
                                 const int cycleDays,
                                 const int nRuns,
                                 eGameBoard& board) :
    eObject(board),
    mEvent(event),
    mStartDate(startDate),
    mPeriodDays(cycleDays),
    mTotNRuns(nRuns),
    mRemNRuns(nRuns),
    mNextDate(startDate) {}

eGameEventCycle::eGameEventCycle(const stdsptr<eGameEvent>& event,
                                 const eDate& date, eGameBoard& board) :
    eGameEventCycle(event, date, 0, 1, board) {}

eGameEventCycle::eGameEventCycle(eGameBoard& board) :
    eObject(board) {}

void eGameEventCycle::addWarning(const int daysBefore,
                                 const stdsptr<eGameEvent>& event) {
    auto& board = getBoard();
    const auto startDate = mStartDate - daysBefore;
    const auto cycle = e::make_shared<eGameEventCycle>(
                event, startDate, mPeriodDays, mTotNRuns, board);
    mWarnings.emplace_back(daysBefore, cycle);
}

void eGameEventCycle::addConsequence(
        const stdsptr<eGameEventCycle>& event) {
    mConsequences.push_back(event);
}

std::string eGameEventCycle::longName() const {
    const auto dateStr = mStartDate.shortString();
    const auto eventName = mEvent->longName();
    return dateStr + " " + eventName;
}

void eGameEventCycle::setStartDate(const eDate& d) {
    mStartDate = d;
    for(const auto& w : mWarnings) {
        w.second->setStartDate(d - w.first);
    }
    rewind();
}

void eGameEventCycle::setPeriod(const int p) {
    mPeriodDays = p;
    for(const auto& w : mWarnings) {
        w.second->setPeriod(p);
    }
    rewind();
}

void eGameEventCycle::setRepeat(const int r) {
    mTotNRuns = r;
    for(const auto& w : mWarnings) {
        w.second->setRepeat(r);
    }
    rewind();
}

void eGameEventCycle::handleNewDate(const eDate& date) {
    for(const auto& w : mWarnings) {
        w.second->handleNewDate(date);
    }
    for(const auto& c : mConsequences) {
        c->handleNewDate(date);
    }
    if(finished()) return;
    if(date > mNextDate) {
        trigger();
        mRemNRuns--;
        mNextDate += mPeriodDays;
    }
}

void eGameEventCycle::rewind() {
    const auto& board = getBoard();
    const auto date = board.date();
    rewind(date);
}

void eGameEventCycle::rewind(const eDate& date) {
    for(const auto& w : mWarnings) {
        w.second->rewind(date);
    }
    mConsequences.clear();

    mNextDate = mStartDate;
    mRemNRuns = mTotNRuns;
    if(mPeriodDays <= 0) {
        if(date > mStartDate) mRemNRuns--;
        return;
    }
    while(date > mNextDate) {
        mRemNRuns--;
        if(mRemNRuns <= 0) break;
        mNextDate += mPeriodDays;
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
    dst << mPeriodDays;
    dst << mTotNRuns;
    dst << mRemNRuns;

    dst << mWarnings.size();
    for(const auto& w : mWarnings) {
        dst << w.first;
        w.second->write(dst);
    }

    dst << mConsequences.size();
    for(const auto& c : mConsequences) {
        c->write(dst);
    }
}

void eGameEventCycle::read(eReadStream& src) {
    eGameEventType type;
    src >> type;
    mEvent = eGameEvent::sCreate(type, getBoard());
    mEvent->read(src);
    mNextDate.read(src);
    mStartDate.read(src);
    src >> mPeriodDays;
    src >> mTotNRuns;
    src >> mRemNRuns;

    int nws;
    src >> nws;
    for(int i = 0; i < nws; i++) {
        int days;
        src >> days;
        const auto e = e::make_shared<eGameEventCycle>(*this);
        e->read(src);
        mWarnings.emplace_back(eWarning(days, e));
    }

    int ncs;
    src >> ncs;
    for(int i = 0; i < ncs; i++) {
        const auto e = e::make_shared<eGameEventCycle>(*this);
        e->read(src);
        mConsequences.emplace_back(e);
    }
}
