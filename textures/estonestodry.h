#ifndef ESTONESTODRY_H
#define ESTONESTODRY_H

#include "engine/etile.h"

enum class eStonesToDryId {
    none = 1 << 0,
    small = 1 << 1,
    large = 1 << 2,
    huge = 1 << 3
};

namespace eStonesToDry {
    eStonesToDryId get(eTile* const tile);
};

#endif // ESTONESTODRY_H
