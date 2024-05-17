#ifndef EMONSTERATTACKEVENT_H
#define EMONSTERATTACKEVENT_H

#include "egameevent.h"
#include "characters/monsters/emonster.h"

class eMonsterAttackEvent : public eGameEvent {
public:
    eMonsterAttackEvent(const eGameEventBranch branch,
                        eGameBoard& board);

    eMonsterType type() const { return mType; }
    void setType(const eMonsterType type);

    void trigger() override;
    std::string longName() const override;

    void write(eWriteStream& dst) const override;
    void read(eReadStream& src) override;

    stdsptr<eGameEvent> makeCopy(const std::string& reason) const override;
private:
    eMonsterType mType = eMonsterType::calydonianBoar;
    int mPointId = 0;
};

#endif // EMONSTERATTACKEVENT_H
