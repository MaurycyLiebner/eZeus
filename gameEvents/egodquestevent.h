#ifndef EGODQUESTEVENT_H
#define EGODQUESTEVENT_H

#include "egodquesteventbase.h"

class eGodQuestEvent : public eGodQuestEventBase {
public:
    eGodQuestEvent(const eGameEventBranch branch);
    ~eGodQuestEvent();

    void trigger() override;
    std::string longName() const override;
    bool finished() const override;

    void read(eReadStream& src) override;
    void write(eWriteStream& dst) const override;

    void fulfill();
    void fulfilled();
private:
    stdsptr<eEventTrigger> mFulfilledTrigger;
    bool mFulfilled = false;
};

#endif // EGODQUESTEVENT_H
