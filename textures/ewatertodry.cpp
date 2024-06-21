#include "ewatertodry.h"

#include "ewatertox.h"

int eWaterToDry::get(eTile* const tile,
                     const eWorldDirection dir) {
    return eWaterToX::get(tile, eTerrain::dryBased | eTerrain::beach, dir);
}
