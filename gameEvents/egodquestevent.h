#ifndef EGODQUESTEVENT_H
#define EGODQUESTEVENT_H

#include "egodquesteventbase.h"

class eGodQuestEvent : public eGodQuestEventBase {
public:
    eGodQuestEvent(const eGameEventBranch branch);
    ~eGodQuestEvent();

    void trigger() override;
    std::string longName() const override;

    void fulfill();
    void fulfilled();
private:
    stdsptr<eEventTrigger> mFulfilledTrigger;
};

#endif // EGODQUESTEVENT_H
