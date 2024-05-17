#ifndef EGODQUESTEVENT_H
#define EGODQUESTEVENT_H

#include "egodquesteventbase.h"

class eGodQuestEvent : public eGodQuestEventBase {
public:
    eGodQuestEvent(const eGameEventBranch branch,
                   eGameBoard& board);

    void trigger() override;
    std::string longName() const override;
    stdsptr<eGameEvent> makeCopy(const std::string& reason) const override;
};

#endif // EGODQUESTEVENT_H
