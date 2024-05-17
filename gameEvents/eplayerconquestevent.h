#ifndef EPLAYERCONQUESTEVENT_H
#define EPLAYERCONQUESTEVENT_H

#include "egameevent.h"

#include "characters/eenlistedforces.h"
#include "engine/eworldcity.h"

class ePlayerConquestEvent : public eGameEvent {
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
private:
    eEnlistedForces mForces;
    stdsptr<eWorldCity> mCity;
};

#endif // EPLAYERCONQUESTEVENT_H
