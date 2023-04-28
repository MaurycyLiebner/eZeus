#ifndef EGIFTFROMEVENT_H
#define EGIFTFROMEVENT_H

#include "egameevent.h"

#include "engine/eworldcity.h"

class eGiftFromEvent : public eGameEvent {
public:
    eGiftFromEvent(eGameBoard& board);

    void initialize(const bool postpone,
                    const eResourceType res,
                    const int count,
                    const stdsptr<eWorldCity>& c);

    void trigger() override;
    std::string longName() const override;

    void write(eWriteStream& dst) const override ;
    void read(eReadStream& src) override;

    const stdsptr<eWorldCity>& city() const { return mCity; }
    void setCity(const stdsptr<eWorldCity>& c);

    eResourceType resourceType() const { return mResource; }
    void setResourceType(const eResourceType type);

    int resourceCount() const { return mCount; }
    void setResourceCount(const int c);
private:
    bool mPostpone;
    eResourceType mResource = eResourceType::fleece;
    int mCount = 16;
    stdsptr<eWorldCity> mCity;
};

#endif // EGIFTFROMEVENT_H
