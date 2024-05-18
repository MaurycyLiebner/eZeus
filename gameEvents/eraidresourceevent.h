#ifndef ERAIDRESOURCEEVENT_H
#define ERAIDRESOURCEEVENT_H

#include "eresourcegrantedeventbase.h"

class eRaidResourceEvent : public eResourceGrantedEventBase {
public:
    eRaidResourceEvent(const eGameEventBranch branch,
                       eGameBoard& board);

    std::string longName() const override;

    stdsptr<eGameEvent> makeCopy(const std::string& reason) const override;
};

#endif // ERAIDRESOURCEEVENT_H
