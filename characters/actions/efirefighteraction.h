#ifndef EFIREFIGHTERACTION_H
#define EFIREFIGHTERACTION_H

#include "epatrolaction.h"

class eFireFighterAction : public ePatrolAction {
public:
    using ePatrolAction::ePatrolAction;

    void increment(const int by);
private:
    bool lookForFire();
    void putOutFire(eTile* const tile);

    bool mFireFighting{false};
    int mFireCheck{0};
};

#endif // EFIREFIGHTERACTION_H
