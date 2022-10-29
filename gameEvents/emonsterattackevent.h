#ifndef EMONSTERATTACKEVENT_H
#define EMONSTERATTACKEVENT_H

#include "egameevent.h"
#include "characters/monsters/emonster.h"

class eMonsterAttackEvent : public eGameEvent {
public:
    eMonsterAttackEvent(eGameBoard& board);

    const std::vector<eMonsterType>& types() const { return mTypes; }
    void setTypes(const std::vector<eMonsterType>& types);

    void setRandom(const bool r);

    void trigger() override;

    void write(eWriteStream& dst) const override ;
    void read(eReadStream& src) override;
private:
    std::vector<eMonsterType> mTypes;
    int mNextId = 0;
    bool mRandom = false;
};

#endif // EMONSTERATTACKEVENT_H
