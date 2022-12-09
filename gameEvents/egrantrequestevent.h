#ifndef EGRANTREQUESTEVENT_H
#define EGRANTREQUESTEVENT_H

#include "egameevent.h"

#include "engine/eresourcetype.h"
#include "engine/eworldcity.h"

class eGrantRequestEvent : public eGameEvent {
public:
    eGrantRequestEvent(const stdsptr<eWorldCity>& c,
                       const eResourceType type,
                       eGameBoard& board);

    void trigger() override;

    void write(eWriteStream& dst) const override ;
    void read(eReadStream& src) override;
private:
    eResourceType mType;
    stdsptr<eWorldCity> mCity;
};

#endif // EGRANTREQUESTEVENT_H
