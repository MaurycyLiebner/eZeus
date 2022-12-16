#ifndef EINVASIONEVENT_H
#define EINVASIONEVENT_H

#include "egameevent.h"

#include "engine/eworldcity.h"

class eInvasionEvent : public eGameEvent {
public:
    eInvasionEvent(eGameBoard& board);

    void initialize(const int stage,
                    const stdsptr<eWorldCity>& city);

    void setArmy(const int infantry,
                 const int cavalry,
                 const int archers);

    void trigger() override;

    void write(eWriteStream& dst) const override ;
    void read(eReadStream& src) override;
private:
    int bribeCost() const;

    int mStage = 0;
    stdsptr<eWorldCity> mCity;

    int mInfantry = 10;
    int mCavalry = 10;
    int mArchers = 10;
};

#endif // EINVASIONEVENT_H
