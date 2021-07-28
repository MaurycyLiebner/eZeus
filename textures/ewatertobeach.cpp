#include "ewatertobeach.h"

#include "ewatertox.h"

int eWaterToBeach::get(eTile* const tile) {
    return eWaterToX::get(tile, eTerrain::beach);
}
