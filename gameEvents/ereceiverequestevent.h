#ifndef ERECEIVEREQUESTEVENT_H
#define ERECEIVEREQUESTEVENT_H

#include "egameevent.h"

#include "engine/eworldcity.h"

struct eReason;
struct eCityRequest;

class eReceiveRequestEvent : public eGameEvent {
public:
    eReceiveRequestEvent(const eGameEventBranch branch);
    ~eReceiveRequestEvent();

    void initialize(const int postpone,
                    const eResourceType res,
                    const int count,
                    const stdsptr<eWorldCity>& c,
                    const bool finish = false);

    void trigger() override;
    std::string longName() const override;

    void write(eWriteStream& dst) const override;
    void read(eReadStream& src) override;

    const stdsptr<eWorldCity>& city() const { return mCity; }
    void setCity(const stdsptr<eWorldCity>& c);

    eResourceType resourceType() const { return mResource; }
    void setResourceType(const eResourceType type);

    int resourceCount() const { return mCount; }
    void setResourceCount(const int c);

    eCityRequest cityRequest() const;
    void dispatch();
    void fulfillWithoutCost();

    void setTributeRequest(const bool t) { mTributeRequest = t; }
    bool tributeRequest() const { return mTributeRequest; }
private:
    void finished(eEventTrigger& t, const eReason& r);

    bool mTributeRequest = false;

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
