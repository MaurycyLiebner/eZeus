#ifndef EREQUESTAIDEVENT_H
#define EREQUESTAIDEVENT_H

#include "egameevent.h"

class eRequestAidEvent : public eGameEvent {
public:
    eRequestAidEvent(const eGameEventBranch branch);

    void trigger() override;
    std::string longName() const override;

    void write(eWriteStream& dst) const override;
    void read(eReadStream& src) override;

    void setCity(const stdsptr<eWorldCity>& c) { mCity = c; }
    const stdsptr<eWorldCity>& city() const { return mCity; }

    void setEnd(const int e) { mEnd = e; }
    bool end() const { return mEnd; }

    void setArrivalDate(const eDate& d) { mArrivalDate = d; }
    const eDate& arrivalDate() const { return mArrivalDate; }
private:
    eDate mArrivalDate;
    bool mEnd = false;
    stdsptr<eWorldCity> mCity;
};

#endif // EREQUESTAIDEVENT_H
