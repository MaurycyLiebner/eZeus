#ifndef EPLAYERCONQUESTEVENTBASE_H
#define EPLAYERCONQUESTEVENTBASE_H

#include "egameevent.h"

#include "characters/eenlistedforces.h"
#include "engine/eworldcity.h"

class ePlayerConquestEventBase : public eGameEvent {
public:
    using eGameEvent::eGameEvent;

    static const int sWaitTime = 50;
    void addAres();
protected:
    void postTrigger();

    eEnlistedForces mForces;
    stdsptr<eWorldCity> mCity;
};

#endif // EPLAYERCONQUESTEVENTBASE_H
