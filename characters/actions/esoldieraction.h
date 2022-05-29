#ifndef ESOLDIERACTION_H
#define ESOLDIERACTION_H

#include "ecomplexaction.h"

#include <map>

#include "eforce.h"

enum class eForceType {
    reserved1, // -1
    regular
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

    void moveBy(const double dx, const double dy);
private:
    int mForceId = 0;
    std::map<int, eForceGetter> mForceGetters;
    double mAngle{0.};

    int mAttackTime = 0;
    bool mAttack = false;
    stdptr<eCharacter> mAttackTarget;
};

#endif // ESOLDIERACTION_H
