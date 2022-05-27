#ifndef ESOLDIERACTION_H
#define ESOLDIERACTION_H

#include "ecomplexaction.h"

#include <map>

struct eForce {
    double fDx;
    double fDy;

    eForce operator+(const eForce& f2) {
        return {fDx + f2.fDx, fDy + f2.fDy};
    }

    eForce operator+=(const eForce& f2) {
        *this = this->operator+(f2);
        return *this;
    }
};

class eSoldierAction : public eComplexAction {
public:
    using eComplexAction::eComplexAction;

    void increment(const int by);

    using eForceGetter = std::function<eForce()>;
    int addForce(const eForceGetter& force);
    void removeForce(const int id);

    void moveBy(const double dx, const double dy);
private:
    int mForceId = 0;
    std::map<int, eForceGetter> mForceGetters;
};

#endif // ESOLDIERACTION_H
