#ifndef EGRANTGENERALREQUESTEVENT_H
#define EGRANTGENERALREQUESTEVENT_H

#include "egameevent.h"

#include "engine/eworldcity.h"

class eGrantGeneralRequestEvent : public eGameEvent {
public:
    eGrantGeneralRequestEvent(eGameBoard& board);

    void initialize(const int postpone,
                    const eResourceType res,
                    const int count,
                    const stdsptr<eWorldCity>& c);

    void trigger() override;

    void write(eWriteStream& dst) const override ;
    void read(eReadStream& src) override;
private:
    int mPostpone;
    eResourceType mResource;
    int mCount;
    stdsptr<eWorldCity> mCity;
};

#endif // EGRANTGENERALREQUESTEVENT_H
