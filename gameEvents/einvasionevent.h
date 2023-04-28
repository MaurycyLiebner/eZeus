#ifndef EINVASIONEVENT_H
#define EINVASIONEVENT_H

#include "egameevent.h"

#include "engine/eworldcity.h"

class eInvasionEvent : public eGameEvent {
public:
    eInvasionEvent(eGameBoard& board);

    void initialize(const int stage,
                    const stdsptr<eWorldCity>& city,
                    const int infantry,
                    const int cavalry,
                    const int archers);

    void trigger() override;
    std::string longName() const override;

    void write(eWriteStream& dst) const override ;
    void read(eReadStream& src) override;

    const stdsptr<eWorldCity>& city() const { return mCity; }
    void setCity(const stdsptr<eWorldCity>& c);

    int infantry() const { return mInfantry; }
    void setInfantry(const int i) { mInfantry = i; }
    int cavalry() const { return mCavalry; }
    void setCavalry(const int c) { mCavalry = c; }
    int archers() const { return mArchers; }
    void setArchers(const int a) { mArchers = a; }
private:
    int bribeCost() const;

    int mStage = 0;
    stdsptr<eWorldCity> mCity;

    int mInfantry = 10;
    int mCavalry = 10;
    int mArchers = 10;
};

#endif // EINVASIONEVENT_H
