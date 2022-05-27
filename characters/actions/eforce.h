#ifndef EFORCE_H
#define EFORCE_H

#include "characters/echaracter.h"

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

namespace eForceHelpers {
    eForce avoidBuildingsForce(eCharacter* const c);
}

#endif // EFORCE_H
