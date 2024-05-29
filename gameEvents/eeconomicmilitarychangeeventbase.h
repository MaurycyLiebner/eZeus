#ifndef EECONOMICMILITARYCHANGEEVENTBASE_H
#define EECONOMICMILITARYCHANGEEVENTBASE_H

#include "egameevent.h"

class eEconomicMilitaryChangeEventBase : public eGameEvent {
public:
    using eGameEvent::eGameEvent;

    void write(eWriteStream& dst) const override;
    void read(eReadStream& src) override;

    void setCity(const stdsptr<eWorldCity>& c) { mCity = c; }
    const stdsptr<eWorldCity>& city() const { return mCity; }

    void setBy(const int b) { mBy = b; }
    int by() const { return mBy; }
private:
    int mBy = 0;
    stdsptr<eWorldCity> mCity;
};

#endif // EECONOMICMILITARYCHANGEEVENTBASE_H
