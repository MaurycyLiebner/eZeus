#ifndef EGODVISITEVENT_H
#define EGODVISITEVENT_H

#include "egameevent.h"
#include "characters/gods/egod.h"

class eGodVisitEvent : public eGameEvent {
public:
    eGodVisitEvent(const eGameEventBranch branch,
                   eGameBoard& board);

    const std::vector<eGodType>& types() const { return mTypes; }
    void setTypes(const std::vector<eGodType>& types);

    void setRandom(const bool r);

    void trigger() override;
    std::string longName() const override;

    void write(eWriteStream& dst) const override;
    void read(eReadStream& src) override;

    stdsptr<eGameEvent> makeCopy(const std::string& reason) const override;
private:
    std::vector<eGodType> mTypes;
    int mNextId = 0;
    bool mRandom = false;
};

#endif // EGODVISITEVENT_H
