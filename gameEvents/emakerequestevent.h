#ifndef EMAKEREQUESTEVENT_H
#define EMAKEREQUESTEVENT_H

#include "egameevent.h"

#include "engine/eworldcity.h"

class eMakeRequestEvent : public eGameEvent {
public:
    eMakeRequestEvent(eGameBoard& board);

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

#endif // EMAKEREQUESTEVENT_H
