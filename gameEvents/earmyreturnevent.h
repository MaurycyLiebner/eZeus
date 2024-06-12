#ifndef EARMYRETURNEVENT_H
#define EARMYRETURNEVENT_H

#include "earmyeventbase.h"

class eArmyReturnEvent : public eArmyEventBase {
public:
    eArmyReturnEvent(const eGameEventBranch branch,
                     eGameBoard* const board);

    void initialize(const eEnlistedForces& forces,
                    const stdsptr<eWorldCity>& city);

    void trigger() override;
    std::string longName() const override;

    stdsptr<eGameEvent> makeCopy(const std::string& reason) const override;
};


#endif // EARMYRETURNEVENT_H
