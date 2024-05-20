#ifndef EPLAYERRAIDEVENT_H
#define EPLAYERRAIDEVENT_H

#include "eplayerconquesteventbase.h"

class ePlayerRaidEvent : public ePlayerConquestEventBase {
public:
    ePlayerRaidEvent(const eGameEventBranch branch,
                     eGameBoard& board);

    void initialize(const eEnlistedForces& forces,
                    const stdsptr<eWorldCity>& city,
                    const eResourceType resource);

    void trigger() override;
    std::string longName() const override;

    void write(eWriteStream& dst) const override;
    void read(eReadStream& src) override;

    stdsptr<eGameEvent> makeCopy(const std::string& reason) const override;
private:
    eResourceType mResource;
};

#endif // EPLAYERRAIDEVENT_H
