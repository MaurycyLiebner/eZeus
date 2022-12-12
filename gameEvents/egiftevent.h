#ifndef EGIFTEVENT_H
#define EGIFTEVENT_H

#include "egameevent.h"

#include "engine/eworldcity.h"

class eGiftEvent : public eGameEvent {
public:
    eGiftEvent(eGameBoard& board);

    void initialize(const stdsptr<eWorldCity>& c,
                    const eResourceType type,
                    const int count);

    void trigger() override;

    void write(eWriteStream& dst) const override ;
    void read(eReadStream& src) override;
private:
    stdsptr<eWorldCity> mCity;
    eResourceType mResource;
    int mCount;
};

#endif // EGIFTEVENT_H
