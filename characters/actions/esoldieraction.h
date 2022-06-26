#ifndef ESOLDIERACTION_H
#define ESOLDIERACTION_H

#include "ecomplexaction.h"

#include <map>

#include "eforce.h"

class eSoldier;

enum class eForceType {
    reserved1, // -1
    regular
};

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

    void increment(const int by);

    using eForceGetter = std::function<vec2d(eCharacter* const)>;
    int addForce(const eForceGetter& force,
                 const eForceType type = eForceType::regular);
    void removeForce(const int id);
    void removeForce(const eForceType type);
    bool hasForce(const eForceType type) const;

    void moveBy(const double dx, const double dy);

    void requestPathForceTask(const int fx, const int fy,
                              const int dist = 0);
    void processPathForceTask();
    void setPathForce(const int sx, const int sy,
                      const int fx, const int fy,
                      const int dist = 0);

    void beingAttacked(eSoldier* const ss);
    void beingAttacked(const int ttx, const int tty);
private:
    void goBackToBanner();

    int mTaskCounter = 0;
    const int mTaskCountCheckBase = 60;
    int mTaskCountCheck = mTaskCountCheckBase;
    ePathForceTask mTask;

    int mForceId = 0;
    std::map<int, eForceGetter> mForceGetters;
    double mAngle{0.};

    int mMissile = 0;

    int mRangeAttack = 0;

    int mLookForEnemy = 0;
    int mAttackTime = 0;
    bool mAttack = false;
    eAttackTarget mAttackTarget;
};

#endif // ESOLDIERACTION_H
