#ifndef ESOLDIERACTION_H
#define ESOLDIERACTION_H

#include "ecomplexaction.h"

#include <map>

#include "eforce.h"

class eSoldier;

class eAttackTarget {
public:
    eAttackTarget();
    eAttackTarget(eCharacter* const c);
    eAttackTarget(eBuilding* const b);

    eTile* tile() const;
    bool valid() const;
    bool defend(const double a);
    bool dead() const;
    void clear();

    double absX() const;
    double absY() const;
private:
    stdptr<eCharacter> mC;
    stdptr<eBuilding> mB;
};

struct ePathForceTask {
    int fFX;
    int fFY;
    int fDist = 0;
    bool fValid = false;
};

class eSoldierAction : public eComplexAction {
public:
    using eComplexAction::eComplexAction;

    bool decide();

    void increment(const int by);

    void moveBy(const double dx, const double dy);

    void goTo(const int fx, const int fy, const int dist = 0);
    void goHome();
    void goBackToBanner();

    void beingAttacked(eSoldier* const ss);
    void beingAttacked(const int ttx, const int tty);

    static eBuilding* sFindHome(const eCharacterType t,
                                const eGameBoard& brd);
private:
    int mTaskCounter = 0;
    const int mTaskCountCheckBase = 60;
    int mTaskCountCheck = mTaskCountCheckBase;
    ePathForceTask mTask;

    int mForceId = 0;
    double mAngle{0.};

    int mMissile = 0;

    int mRangeAttack = 0;

    int mLookForEnemy = 0;
    int mAttackTime = 0;
    bool mAttack = false;
    eAttackTarget mAttackTarget;
};

#endif // ESOLDIERACTION_H
