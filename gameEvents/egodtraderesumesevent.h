#ifndef EGODTRADERESUMESEVENT_H
#define EGODTRADERESUMESEVENT_H

#include "egameevent.h"

#include "characters/gods/egod.h"

class eGodTradeResumesEvent : public eGameEvent {
public:
    eGodTradeResumesEvent(const eGameEventBranch branch);

    void trigger() override;
    std::string longName() const override;

    void write(eWriteStream& dst) const override;
    void read(eReadStream& src) override;

    void setGod(const eGodType god) { mGod = god; }
    eGodType god() const { return mGod; }
private:
    eGodType mGod = eGodType::zeus;
};

#endif // EGODTRADERESUMESEVENT_H
