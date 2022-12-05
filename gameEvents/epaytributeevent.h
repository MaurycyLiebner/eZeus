#ifndef EPAYTRIBUTEEVENT_H
#define EPAYTRIBUTEEVENT_H

#include "egameevent.h"

#include "engine/eworldcity.h"

class ePayTributeEvent : public eGameEvent {
public:
    ePayTributeEvent(eGameBoard& board);

    void setCity(const stdsptr<eWorldCity>& city);

    void trigger() override;

    void write(eWriteStream& dst) const override ;
    void read(eReadStream& src) override;
private:
    stdsptr<eWorldCity> mCity;
};

#endif // EPAYTRIBUTEEVENT_H
