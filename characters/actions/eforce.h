#ifndef EFORCE_H
#define EFORCE_H

#include "characters/echaracter.h"
#include "vec2.h"

namespace eForceHelpers {
    vec2d avoidUnwalkableForce(eCharacter* const c);
    vec2d avoidSoldiersForce(eCharacter* const c);
}

#endif // EFORCE_H
