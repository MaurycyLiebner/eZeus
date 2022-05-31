#ifndef EARCHERACTION_H
#define EARCHERACTION_H

#include "ecomplexaction.h"
#include "pointers/estdpointer.h"

class eArcherAction : public eComplexAction {
public:
    using eComplexAction::eComplexAction;

    void increment(const int by);
    bool decide();
private:
    int mMissile = 0;
    int mRangeAttack = 0;
    int mAttackTime = 0;
    bool mAttack = false;
    stdptr<eCharacter> mAttackTarget;
};

#endif // EARCHERACTION_H
