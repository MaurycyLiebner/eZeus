#ifndef ESUPPLYDEMANDCHANGEEVENT_H
#define ESUPPLYDEMANDCHANGEEVENT_H

#include "ebasiccityevent.h"

#include "engine/eresourcetype.h"

class eSupplyDemandChangeEvent : public eBasicCityEvent {
public:
    using eBasicCityEvent::eBasicCityEvent;

    void write(eWriteStream& dst) const override;
    void read(eReadStream& src) override;

    eResourceType type() const { return mType; }
    void setType(const eResourceType type) { mType = type; }

    int by() const { return mBy; }
    void setBy(const int by) { mBy = by; }
private:
    eResourceType mType;
    int mBy = 0;
};

#endif // ESUPPLYDEMANDCHANGEEVENT_H
