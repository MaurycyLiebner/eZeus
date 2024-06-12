#ifndef EMONSTERUNLEASHEDEVENT_H
#define EMONSTERUNLEASHEDEVENT_H

#include "emonsterinvasioneventbase.h"

class eMonsterUnleashedEvent : public eMonsterInvasionEventBase {
public:
    eMonsterUnleashedEvent(const eGameEventBranch branch);

    void trigger() override;
    std::string longName() const override;

    stdsptr<eGameEvent> makeCopy(const std::string& reason) const override;
};

#endif // EMONSTERUNLEASHEDEVENT_H
