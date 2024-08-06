#ifndef EBASICCITYEVENT_H
#define EBASICCITYEVENT_H

#include "egameevent.h"

class eBasicCityEvent : public eGameEvent {
public:
    using eGameEvent::eGameEvent;

    void write(eWriteStream& dst) const override;
    void read(eReadStream& src) override;

    void setCity(const stdsptr<eWorldCity>& c) { mCity = c; }
    const stdsptr<eWorldCity>& city() const { return mCity; }
private:
    stdsptr<eWorldCity> mCity;
};

#endif // EBASICCITYEVENT_H
