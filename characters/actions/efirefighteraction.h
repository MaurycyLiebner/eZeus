#ifndef EFIREFIGHTERACTION_H
#define EFIREFIGHTERACTION_H

#include "epatrolaction.h"

class eFireFighterAction : public ePatrolAction {
public:
    eFireFighterAction(eCharacter* const c,
                       const std::vector<ePatrolGuide>& guides,
                       const eAction& failAction,
                       const eAction& finishAction);

    void increment(const int by);
private:
    bool lookForFire();
    void putOutFire(eTile* const tile);

    int mFireCheck{0};
};

#endif // EFIREFIGHTERACTION_H
