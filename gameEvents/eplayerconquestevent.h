#ifndef EPLAYERCONQUESTEVENT_H
#define EPLAYERCONQUESTEVENT_H

#include "eplayerconquesteventbase.h"

class ePlayerConquestEvent : public ePlayerConquestEventBase {
public:
    ePlayerConquestEvent(const eGameEventBranch branch,
                         eGameBoard* const board);

    void initialize(const eEnlistedForces& forces,
                    const stdsptr<eWorldCity>& city);

    void trigger() override;
    std::string longName() const override;
};

#endif // EPLAYERCONQUESTEVENT_H
