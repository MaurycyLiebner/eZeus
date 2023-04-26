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
private:
    bool mPostpone;
    eResourceType mResource;
    int mCount;
    stdsptr<eWorldCity> mCity;
};

#endif // EGIFTFROMEVENT_H
