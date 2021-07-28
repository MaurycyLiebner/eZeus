#include "ewatertodry.h"

#include "ewatertox.h"

int eWaterToDry::get(eTile* const tile) {
    return eWaterToX::get(tile, eTerrain::dryBased);
}
