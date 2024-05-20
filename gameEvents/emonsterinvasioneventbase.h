#ifndef EMONSTERINVASIONEVENTBASE_H
#define EMONSTERINVASIONEVENTBASE_H

#include "egameevent.h"
#include "characters/monsters/emonster.h"

class eMonsterInvasionEventBase : public eGameEvent {
public:
    eMonsterInvasionEventBase(const eGameEventType type,
                              const eGameEventBranch branch,
                              eGameBoard& board);

    eMonsterType type() const { return mType; }
    void setType(const eMonsterType type);

    int pointId() const { return mPointId; }
    void setPointId(const int p);

    void write(eWriteStream& dst) const override;
    void read(eReadStream& src) override;
protected:
    eMonster* triggerBase() const;
private:
    eMonsterType mType = eMonsterType::calydonianBoar;
    int mPointId = 0;
};

#endif // EMONSTERINVASIONEVENTBASE_H
