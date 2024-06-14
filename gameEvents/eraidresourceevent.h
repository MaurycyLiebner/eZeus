#ifndef ERAIDRESOURCEEVENT_H
#define ERAIDRESOURCEEVENT_H

#include "eresourcegrantedeventbase.h"

class eRaidResourceEvent : public eResourceGrantedEventBase {
public:
    eRaidResourceEvent(const eGameEventBranch branch);

    std::string longName() const override;
};

#endif // ERAIDRESOURCEEVENT_H
