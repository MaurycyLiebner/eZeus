#ifndef ERECEIVEREQUESTEVENT_H
#define ERECEIVEREQUESTEVENT_H

#include "egameevent.h"

#include "engine/eworldcity.h"

struct eReason;
struct eCityRequest;

class eReceiveRequestEvent : public eGameEvent {
public:
    eReceiveRequestEvent(const eGameEventBranch branch,
                         eGameBoard& board);

    void initialize(const int postpone,
                    const eResourceType res,
                    const int count,
                    const stdsptr<eWorldCity>& c,
                    const bool finish = false);

    void trigger() override;
    std::string longName() const override;

    void write(eWriteStream& dst) const override;
    void read(eReadStream& src) override;

    stdsptr<eGameEvent> makeCopy(const std::string& reason) const override;

    const stdsptr<eWorldCity>& city() const { return mCity; }
    void setCity(const stdsptr<eWorldCity>& c);

    eResourceType resourceType() const { return mResource; }
    void setResourceType(const eResourceType type);

    int resourceCount() const { return mCount; }
    void setResourceCount(const int c);

    eCityRequest cityRequest() const;
    void dispatch();
private:
    void finished(eEventTrigger& t, const eReason& r);

    bool mFinish = false;
    int mPostpone = 0;
    eResourceType mResource = eResourceType::fleece;
    int mCount = 16;
    stdsptr<eWorldCity> mCity;

    stdsptr<eEventTrigger> mEarlyTrigger;
    stdsptr<eEventTrigger> mComplyTrigger;
    stdsptr<eEventTrigger> mTooLateTrigger;
    stdsptr<eEventTrigger> mRefuseTrigger;
};

#endif // ERECEIVEREQUESTEVENT_H
