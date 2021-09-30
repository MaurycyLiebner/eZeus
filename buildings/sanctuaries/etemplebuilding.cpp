#include "etemplebuilding.h"

#include "textures/egametextures.h"

eTempleBuilding::eTempleBuilding(eGameBoard& board) :
    eSanctBuilding(board, eBuildingType::temple, 4, 4) {
    setEnabled(true);
}
