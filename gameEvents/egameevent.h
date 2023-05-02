#ifndef EGAMEEVENT_H
#define EGAMEEVENT_H

#include "pointers/eobject.h"

#include "engine/edate.h"

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
    giftFrom
};

class eGameEvent : public eObject {
public:
    using eAction = std::function<void()>;
    eGameEvent(const eGameEventType type, eGameBoard& board);

    virtual void trigger() = 0;

    virtual std::string longName() const = 0;

    virtual void write(eWriteStream& dst) const;
    virtual void read(eReadStream& src);

    static stdsptr<eGameEvent> sCreate(const eGameEventType type,
                                       eGameBoard& board);

    eGameEventType type() const { return mType; }

    void initializeDate(const eDate& startDate,
                        const int cycleDays = 0,
                        const int nRuns = 1);

    void addWarning(const int daysBefore,
                    const stdsptr<eGameEvent>& event);
    void clearWarnings();
    void addConsequence(const stdsptr<eGameEvent>& event);

    std::string longDatedName() const;

    const eDate& startDate() const { return mStartDate; }
    void setStartDate(const eDate& d);

    int period() const { return mPeriodDays; }
    void setPeriod(const int p);

    int repeat() const { return mTotNRuns; }
    void setRepeat(const int r);

    void handleNewDate(const eDate& date);
    void rewind();
    void rewind(const eDate& date);
    bool finished() const { return mRemNRuns <= 0; }

    using eWarning = std::pair<int, stdsptr<eGameEvent>>;
    const std::vector<eWarning>& warnings() const { return mWarnings; }
private:
    const eGameEventType mType;

    std::vector<eWarning> mWarnings;
    std::vector<stdsptr<eGameEvent>> mConsequences;

    eDate mStartDate;
    int mPeriodDays;
    int mTotNRuns;

    int mRemNRuns;
    eDate mNextDate;
};

#endif // EGAMEEVENT_H
