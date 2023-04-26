#ifndef EGIFTTOEVENT_H
#define EGIFTTOEVENT_H

#include "egameevent.h"

#include "engine/eworldcity.h"

class eGiftToEvent : public eGameEvent {
public:
    eGiftToEvent(eGameBoard& board);

    void initialize(const stdsptr<eWorldCity>& c,
                    const eResourceType type,
                    const int count);

    void trigger() override;
    std::string longName() const override;

    void write(eWriteStream& dst) const override ;
    void read(eReadStream& src) override;
private:
    stdsptr<eWorldCity> mCity;
    eResourceType mResource;
    int mCount;
};

#endif // EGIFTTOEVENT_H
