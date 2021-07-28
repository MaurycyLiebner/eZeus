#ifndef ESTONESTODRY_H
#define ESTONESTODRY_H

#include "engine/etile.h"

enum class eStonesToDryId {
    doubleInner, inner, outer
};

namespace eStonesToDry {
    eStonesToDryId get(eTile* const tile);
};

#endif // ESTONESTODRY_H
