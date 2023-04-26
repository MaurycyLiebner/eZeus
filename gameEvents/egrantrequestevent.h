#ifndef EGRANTREQUESTEVENT_H
#define EGRANTREQUESTEVENT_H

#include "egameevent.h"

#include "engine/eworldcity.h"

class eGrantRequestEvent : public eGameEvent {
public:
    eGrantRequestEvent(eGameBoard& board);

    void initialize(const bool postpone,
                    const eResourceType res,
                    const stdsptr<eWorldCity>& c);

    void trigger() override;
    std::string longName() const override;

    void write(eWriteStream& dst) const override ;
    void read(eReadStream& src) override;
private:
    bool mPostpone;
    eResourceType mResource;
    stdsptr<eWorldCity> mCity;
};

#endif // EGRANTREQUESTEVENT_H
