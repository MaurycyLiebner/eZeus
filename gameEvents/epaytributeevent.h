#ifndef EPAYTRIBUTEEVENT_H
#define EPAYTRIBUTEEVENT_H

#include "egameevent.h"

#include "engine/eworldcity.h"

class ePayTributeEvent : public eGameEvent {
public:
    ePayTributeEvent(const eGameEventBranch branch);

    void initialize(const stdsptr<eWorldCity>& c);

    void trigger() override;
    std::string longName() const override;

    void write(eWriteStream& dst) const override;
    void read(eReadStream& src) override;

    stdsptr<eGameEvent> makeCopy(const std::string& reason) const override;
private:
    stdsptr<eWorldCity> mCity;
};

#endif // EPAYTRIBUTEEVENT_H
