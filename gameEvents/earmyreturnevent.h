#ifndef EARMYRETURNEVENT_H
#define EARMYRETURNEVENT_H

#include "egameevent.h"
#include "characters/eenlistedforces.h"
#include "engine/eworldcity.h"

class eArmyReturnEvent : public eGameEvent {
public:
    eArmyReturnEvent(const eGameEventBranch branch,
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


#endif // EARMYRETURNEVENT_H
