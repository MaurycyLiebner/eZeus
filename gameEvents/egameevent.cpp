#include "egameevent.h"

#include "engine/egameboard.h"

#include "egodvisitevent.h"
#include "egodattackevent.h"
#include "emonsterattackevent.h"
#include "einvasionevent.h"
#include "einvasionwarningevent.h"
#include "epaytributeevent.h"
#include "emakerequestevent.h"
#include "ereceiverequestevent.h"
#include "egifttoevent.h"
#include "egiftfromevent.h"
#include "egodquestevent.h"
#include "egodquestfulfilledevent.h"
#include "eplayerconquestevent.h"
#include "earmyreturnevent.h"

eGameEvent::eGameEvent(const eGameEventType type,
                       const eGameEventBranch branch,
                       eGameBoard& board) :
    eObject(board), mType(type), mBranch(branch) {
    board.addGameEvent(this);
}

eGameEvent::~eGameEvent() {
    auto& board = getBoard();
    board.removeGameEvent(this);
}

stdsptr<eGameEvent> eGameEvent::sCreate(const eGameEventType type,
                                        const eGameEventBranch branch,
                                        eGameBoard& board) {
    switch(type) {
    case eGameEventType::godVisit:
        return e::make_shared<eGodVisitEvent>(branch, board);
    case eGameEventType::godAttack:
        return e::make_shared<eGodAttackEvent>(branch, board);
    case eGameEventType::monsterAttack:
        return e::make_shared<eMonsterAttackEvent>(branch, board);
    case eGameEventType::invasion:
        return e::make_shared<eInvasionEvent>(branch, board);
    case eGameEventType::invasionWarning:
        return e::make_shared<eInvasionWarningEvent>(branch, board);
    case eGameEventType::payTribute:
        return e::make_shared<ePayTributeEvent>(branch, board);
    case eGameEventType::makeRequest:
        return e::make_shared<eMakeRequestEvent>(branch, board);
    case eGameEventType::receiveRequest:
        return e::make_shared<eReceiveRequestEvent>(branch, board);
    case eGameEventType::giftTo:
        return e::make_shared<eGiftToEvent>(branch, board);
    case eGameEventType::giftFrom:
        return e::make_shared<eGiftFromEvent>(branch, board);
    case eGameEventType::godQuest:
        return e::make_shared<eGodQuestEvent>(branch, board);
    case eGameEventType::godQuestFulfilled:
        return e::make_shared<eGodQuestFulfilledEvent>(branch, board);
    case eGameEventType::playerConquestEvent:
        return e::make_shared<ePlayerConquestEvent>(branch, board);
    case eGameEventType::armyReturnEvent:
        return e::make_shared<eArmyReturnEvent>(branch, board);
    }
    return nullptr;
}

void eGameEvent::initializeDate(const eDate& startDate,
                                const int period,
                                const int nRuns) {
    setStartDate(startDate);
    setPeriod(period);
    setRepeat(nRuns);
    rewind();
}

void eGameEvent::addWarning(const int daysBefore,
                            const stdsptr<eGameEvent>& event) {
    const auto startDate = mStartDate - daysBefore;
    event->initializeDate(startDate, period(), repeat());
    event->setReason(reason());
    mWarnings.emplace_back(daysBefore, event);
}

void eGameEvent::clearWarnings() {
    mWarnings.clear();
}

bool eGameEvent::isMainEvent() const {
    return mBranch != eGameEventBranch::child;
}

bool eGameEvent::isRootEvent() const {
    return mBranch == eGameEventBranch::root;
}

bool eGameEvent::isTriggerEvent() const {
    return mBranch == eGameEventBranch::trigger;
}

bool eGameEvent::isChildEvent() const {
    return mBranch == eGameEventBranch::child;
}

void eGameEvent::addConsequence(const stdsptr<eGameEvent>& event) {
    mConsequences.push_back(event);
    if(event->branch() == eGameEventBranch::child) {
        event->setReason(reason());
    }
    event->mParent = this;
}

void eGameEvent::clearConsequences() {
    mConsequences.clear();
}

bool eGameEvent::hasActiveConsequences(const eDate& date) const {
    for(const auto& c : mConsequences) {
        const auto cDate = c->startDate();
        const auto cc = c->hasActiveConsequences(date);
        const bool cFuture = cDate > date || cc;
        if(cFuture) return true;
    }
    return false;
}

bool eGameEvent::hasActiveNonTriggerConsequences(const eDate& date) const {
    for(const auto& c : mConsequences) {
        const bool te = c->isTriggerEvent();
        if(te) continue;
        const auto cDate = c->startDate();
        const auto cc = c->hasActiveNonTriggerConsequences(date);
        const bool cFuture = cDate > date || cc;
        if(cFuture) return true;
    }
    return false;
}

std::string eGameEvent::longDatedName() const {
    const auto dateStr = mStartDate.shortString();
    const auto eventName = longName();
    return dateStr + " " + eventName;
}

void eGameEvent::setReason(const std::string& r) {
    mReason = r;
    for(const auto& w : mWarnings) {
        w.second->setReason(r);
    }
}

void eGameEvent::setStartDate(const eDate& d) {
    mStartDate = d;
    for(const auto& w : mWarnings) {
        w.second->setStartDate(d - w.first);
    }
    rewind();
}

void eGameEvent::setPeriod(const int p) {
    mPeriodDays = p;
    for(const auto& w : mWarnings) {
        w.second->setPeriod(p);
    }
    rewind();
}

void eGameEvent::setRepeat(const int r) {
    mTotNRuns = r;
    for(const auto& w : mWarnings) {
        w.second->setRepeat(r);
    }
    rewind();
}

void eGameEvent::rewind() {
    const auto& board = getBoard();
    const auto date = board.date();
    rewind(date);
}

void eGameEvent::rewind(const eDate& date) {
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

void eGameEvent::handleNewDate(const eDate& date) {
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

int eGameEvent::triggerEventsCount() const {
    int r = 0;
    for(const auto& t : mTriggers) {
        r += t->eventCount();
    }
    return r;
}

void eGameEvent::addTrigger(const stdsptr<eEventTrigger>& et) {
    mTriggers.push_back(et);
}

void eGameEvent::write(eWriteStream& dst) const {
    dst << mIOID;
    mNextDate.write(dst);
    mStartDate.write(dst);
    dst << mPeriodDays;
    dst << mTotNRuns;
    dst << mRemNRuns;
    dst << mReason;

    dst << mWarnings.size();
    for(const auto& w : mWarnings) {
        const int daysBefore = w.first;
        const auto& event = w.second;
        dst << daysBefore;
        dst << event->type();
        dst << event->branch();
        event->write(dst);
    }

    dst << mConsequences.size();
    for(const auto& c : mConsequences) {
        dst << c->type();
        dst << c->branch();
        c->write(dst);
    }

    for(const auto& et : mTriggers) {
        et->write(dst);
    }
}

void eGameEvent::read(eReadStream& src) {
    src >> mIOID;
    mNextDate.read(src);
    mStartDate.read(src);
    src >> mPeriodDays;
    src >> mTotNRuns;
    src >> mRemNRuns;
    src >> mReason;

    int nws;
    src >> nws;
    for(int i = 0; i < nws; i++) {
        int days;
        src >> days;
        eGameEventType type;
        src >> type;
        eGameEventBranch branch;
        src >> branch;
        const auto e = eGameEvent::sCreate(type, branch, getBoard());
        e->read(src);
        mWarnings.emplace_back(eWarning(days, e));
    }

    int ncs;
    src >> ncs;
    for(int i = 0; i < ncs; i++) {
        eGameEventType type;
        src >> type;
        eGameEventBranch branch;
        src >> branch;
        const auto e = eGameEvent::sCreate(type, branch, getBoard());
        e->read(src);
        addConsequence(e);
    }

    for(const auto& et : mTriggers) {
        et->read(src);
    }
}
