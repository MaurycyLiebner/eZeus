#ifndef ETROOPSREQUESTEVENT_H
#define ETROOPSREQUESTEVENT_H

#include "egameevent.h"

#include "engine/eworldcity.h"

struct eReason;

class eTroopsRequestEvent : public eGameEvent {
public:
    eTroopsRequestEvent(const eGameEventBranch branch);
   ~eTroopsRequestEvent();

    void initialize(const int postpone,
                    const stdsptr<eWorldCity> &c,
                    const stdsptr<eWorldCity> &rival,
                    const bool finish = false);

    void trigger() override;
    std::string longName() const override;

    void write(eWriteStream& dst) const override;
    void read(eReadStream& src) override;

    const stdsptr<eWorldCity>& city() const { return mCity; }
    void setCity(const stdsptr<eWorldCity>& c);

    const stdsptr<eWorldCity>& rivalCity() const { return mRivalCity; }
    void setRivalCity(const stdsptr<eWorldCity>& c);

    using eAction = std::function<void()>;
    void dispatch(const eAction& close = nullptr);

    void won();
    void lost();
private:
    void finished(eEventTrigger& t, const eReason& r);

    bool mFinish = false;
    int mPostpone = 0;
    stdsptr<eWorldCity> mCity;
    stdsptr<eWorldCity> mRivalCity;

    stdsptr<eEventTrigger> mEarlyTrigger;
    stdsptr<eEventTrigger> mComplyTrigger;
    stdsptr<eEventTrigger> mTooLateTrigger;
    stdsptr<eEventTrigger> mRefuseTrigger;
    stdsptr<eEventTrigger> mLostBattleTrigger;
};

#endif // ETROOPSREQUESTEVENT_H
