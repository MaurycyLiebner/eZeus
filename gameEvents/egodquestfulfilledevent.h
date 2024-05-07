#ifndef EGODQUESTFULFILLEDEVENT_H
#define EGODQUESTFULFILLEDEVENT_H

#include "egodquesteventbase.h"

class eGodQuestFulfilledEvent : public eGodQuestEventBase {
public:
    eGodQuestFulfilledEvent(eGameBoard& board);

    void trigger() override;
    std::string longName() const override;
    stdsptr<eGameEvent> makeCopy(const std::string& reason) const override;
};

#endif // EGODQUESTFULFILLEDEVENT_H