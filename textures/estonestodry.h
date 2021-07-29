#ifndef ESTONESTODRY_H
#define ESTONESTODRY_H

#include "engine/etile.h"

enum class eStonesToDryId {
    none, small, large, huge
};

namespace eStonesToDry {
    eStonesToDryId get(eTile* const tile);
};

#endif // ESTONESTODRY_H
