#ifndef EPLAYERRAIDEVENT_H
#define EPLAYERRAIDEVENT_H

#include "eplayerconquesteventbase.h"

class ePlayerRaidEvent : public ePlayerConquestEventBase {
public:
    ePlayerRaidEvent(const eGameEventBranch branch,
                     eGameBoard* const board);

    void initialize(const eEnlistedForces& forces,
                    const stdsptr<eWorldCity>& city,
                    const eResourceType resource);

    void trigger() override;
    std::string longName() const override;

    void write(eWriteStream& dst) const override;
    void read(eReadStream& src) override;
private:
    eResourceType mResource;
};

#endif // EPLAYERRAIDEVENT_H
