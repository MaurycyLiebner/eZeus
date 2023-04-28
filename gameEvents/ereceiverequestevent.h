#ifndef ERECEIVEREQUESTEVENT_H
#define ERECEIVEREQUESTEVENT_H

#include "egameevent.h"

#include "engine/eworldcity.h"

class eReceiveRequestEvent : public eGameEvent {
public:
    eReceiveRequestEvent(eGameBoard& board);

    void initialize(const int postpone,
                    const eResourceType res,
                    const int count,
                    const stdsptr<eWorldCity>& c);

    void trigger() override;
    std::string longName() const override;

    void write(eWriteStream& dst) const override ;
    void read(eReadStream& src) override;
private:
    int mPostpone;
    eResourceType mResource;
    int mCount;
    stdsptr<eWorldCity> mCity;
};

#endif // ERECEIVEREQUESTEVENT_H
