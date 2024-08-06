#ifndef EPRICECHANGEEVENT_H
#define EPRICECHANGEEVENT_H

#include "egameevent.h"

#include "engine/eresourcetype.h"

class ePriceChangeEvent : public eGameEvent {
public:
    ePriceChangeEvent(const eGameEventBranch branch);

    void write(eWriteStream& dst) const override;
    void read(eReadStream& src) override;

    void trigger() override;
    std::string longName() const override;

    eResourceType type() const { return mType; }
    void setType(const eResourceType type) { mType = type; }

    int by() const { return mBy; }
    void setBy(const int by) { mBy = by; }
private:
    eResourceType mType = eResourceType::marble;
    int mBy = 0;
};

#endif // EPRICECHANGEEVENT_H
