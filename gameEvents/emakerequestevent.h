#ifndef EMAKEREQUESTEVENT_H
#define EMAKEREQUESTEVENT_H

#include "egameevent.h"

#include "engine/eworldcity.h"

class eMakeRequestEvent : public eGameEvent {
public:
    eMakeRequestEvent(const eGameEventBranch branch,
                      eGameBoard& board);

    void initialize(const bool postpone,
                    const eResourceType res,
                    const stdsptr<eWorldCity>& c);

    void trigger() override;
    std::string longName() const override;

    void write(eWriteStream& dst) const override;
    void read(eReadStream& src) override;

    stdsptr<eGameEvent> makeCopy(const std::string& reason) const override;

    const stdsptr<eWorldCity>& city() const { return mCity; }
    void setCity(const stdsptr<eWorldCity>& c);

    eResourceType resourceType() const { return mResource; }
    void setResourceType(const eResourceType type);
private:
    bool mPostpone = true;
    eResourceType mResource;
    stdsptr<eWorldCity> mCity;
};

#endif // EMAKEREQUESTEVENT_H
