#ifndef EGAMEEVENT_H
#define EGAMEEVENT_H

#include "pointers/eobject.h"

#include "engine/edate.h"
#include "eeventtrigger.h"

#include <functional>

class eWriteStream;
class eReadStream;

enum class eGameEventType {
    godVisit,
    godAttack,
    monsterAttack,
    invasion,
    invasionWarning,
    payTribute,
    receiveRequest,
    makeRequest,
    giftTo,
    giftFrom,
    godQuest,
    godQuestFulfilled,
    playerConquestEvent,
    playerRaidEvent,
    raidResourceReceive,
    armyReturnEvent
};

enum class eGameEventBranch {
    root,
    child,
    trigger
};

class eGameEvent : public eObject {
public:
    eGameEvent(const eGameEventType type,
               const eGameEventBranch branch,
               eGameBoard& board);
    ~eGameEvent();

    virtual void trigger() = 0;

    virtual std::string longName() const = 0;

    virtual stdsptr<eGameEvent> makeCopy(const std::string& reason) const = 0;

    virtual void write(eWriteStream& dst) const;
    virtual void read(eReadStream& src);

    static stdsptr<eGameEvent> sCreate(const eGameEventType type,
                                       const eGameEventBranch branch,
                                       eGameBoard& board);

    eGameEventType type() const { return mType; }

    void setIOID(const int id) { mIOID = id; }
    int ioID() const { return mIOID; }

    void initializeDate(const eDate& startDate,
                        const int period = 0,
                        const int nRuns = 1);

    bool isMainEvent() const;
    bool isRootEvent() const;
    bool isTriggerEvent() const;
    bool isChildEvent() const;
    eGameEventBranch branch() const { return mBranch; }

    void addWarning(const int daysBefore,
                    const stdsptr<eGameEvent>& event);
    void clearWarnings();

    void addConsequence(const stdsptr<eGameEvent>& event);
    void clearConsequences();
    bool hasActiveConsequences(const eDate& date) const;
    bool hasActiveNonTriggerConsequences(const eDate& date) const;

    template <typename T = eGameEvent>
    T* rootEvent() {
        if(isRootEvent()) return static_cast<T*>(this);
        if(mParent) return mParent->rootEvent<T>();
        return nullptr;
    }

    template <typename T = eGameEvent>
    T* mainEvent() {
        if(isMainEvent()) return static_cast<T*>(this);
        if(mParent) return mParent->mainEvent<T>();
        return nullptr;
    }

    std::string longDatedName() const;

    void setReason(const std::string& r);
    const std::string& reason() const { return mReason; }

    const eDate& startDate() const { return mStartDate; }
    void setStartDate(const eDate& d);

    int period() const { return mPeriodDays; }
    void setPeriod(const int p);

    int repeat() const { return mTotNRuns; }
    void setRepeat(const int r);

    void rewind();
    void rewind(const eDate& date);

    void handleNewDate(const eDate& date);
    bool finished() const { return mRemNRuns <= 0; }

    using eWarning = std::pair<int, stdsptr<eGameEvent>>;
    const std::vector<eWarning>& warnings() const
    { return mWarnings; }

    const std::vector<stdsptr<eEventTrigger>>& triggers() const
    { return mTriggers; }
    int triggerEventsCount() const;
protected:
    void addTrigger(const stdsptr<eEventTrigger>& et);
private:
    const eGameEventType mType;
    const eGameEventBranch mBranch;

    stdptr<eGameEvent> mParent;

    std::vector<stdsptr<eGameEvent>> mConsequences;
    std::vector<eWarning> mWarnings;
    std::vector<stdsptr<eEventTrigger>> mTriggers;

    std::string mReason;

    eDate mStartDate{1, eMonth::january, 1};
    int mPeriodDays = 100;
    int mTotNRuns = 1;

    int mRemNRuns = 0;
    eDate mNextDate = mStartDate;

    int mIOID = -1;
};

#endif // EGAMEEVENT_H
