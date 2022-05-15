#ifndef EFIREFIGHTERACTION_H
#define EFIREFIGHTERACTION_H

#include "epatrolaction.h"

#include "engine/etile.h"

class eFireFighterAction : public ePatrolAction {
public:
    using ePatrolAction::ePatrolAction;

    bool decide();
    void increment(const int by);
private:
    bool lookForFire();
    void putOutFire(eTile* const tile);

    bool mFireFighting{false};
    int mFireCheck{0};

    int mUsedWater = 0;

    stdsptr<eCharacterAction> mMoveToFireAction;
};

#endif // EFIREFIGHTERACTION_H
