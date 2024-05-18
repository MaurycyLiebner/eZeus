#ifndef EGIFTFROMEVENT_H
#define EGIFTFROMEVENT_H

#include "eresourcegrantedeventbase.h"

class eGiftFromEvent : public eResourceGrantedEventBase {
public:
    eGiftFromEvent(const eGameEventBranch branch,
                   eGameBoard& board);

    std::string longName() const override;

    stdsptr<eGameEvent> makeCopy(const std::string& reason) const override;
};

#endif // EGIFTFROMEVENT_H
