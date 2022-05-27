#ifndef ESOLDIERACTION_H
#define ESOLDIERACTION_H

#include "ecomplexaction.h"

#include <map>

#include "eforce.h"

class eSoldierAction : public eComplexAction {
public:
    using eComplexAction::eComplexAction;

    void increment(const int by);

    using eForceGetter = std::function<eForce(eCharacter* const)>;
    int addForce(const eForceGetter& force);
    void removeForce(const int id);

    void moveBy(const double dx, const double dy);
private:
    int mForceId = 0;
    std::map<int, eForceGetter> mForceGetters;
};

#endif // ESOLDIERACTION_H
