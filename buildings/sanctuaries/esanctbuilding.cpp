#include "esanctbuilding.h"

#include "textures/egametextures.h"

eSanctBuilding::eSanctBuilding(eGameBoard& board,
                               const eBuildingType type,
                               const int sw, const int sh) :
    eBuilding(board, type, sw, sh) {
    setOverlayEnabledFunc([]() { return true; });
}
