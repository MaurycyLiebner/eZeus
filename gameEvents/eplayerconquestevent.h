#ifndef EPLAYERCONQUESTEVENT_H
#define EPLAYERCONQUESTEVENT_H

#include "eplayerconquesteventbase.h"

class ePlayerConquestEvent : public ePlayerConquestEventBase {
public:
    ePlayerConquestEvent(const eGameEventBranch branch,
                         eGameBoard& board);

    void initialize(const eEnlistedForces& forces,
                    const stdsptr<eWorldCity>& city);

    void trigger() override;
    std::string longName() const override;

    void write(eWriteStream& dst) const override;
    void read(eReadStream& src) override;

    stdsptr<eGameEvent> makeCopy(const std::string& reason) const override;
};

#endif // EPLAYERCONQUESTEVENT_H
