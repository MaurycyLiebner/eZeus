#include "etemplebuilding.h"

#include "textures/egametextures.h"

eTempleBuilding::eTempleBuilding(eGameBoard& board) :
    eSanctBuilding({5, 5, 0}, 3, board,
                   eBuildingType::temple, 4, 4) {
    setEnabled(true);
}
