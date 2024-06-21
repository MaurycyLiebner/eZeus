#include "ewatertobeach.h"

#include "ewatertox.h"

int eWaterToBeach::get(eTile* const tile,
                       const eWorldDirection dir) {
    return eWaterToX::get(tile, eTerrain::beach, dir);
}
