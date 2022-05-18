#include "etemplebuilding.h"

#include "textures/egametextures.h"

eTempleBuilding::eTempleBuilding(eSanctuary* const s, eGameBoard& board) :
    eSanctBuilding(s, {5, 5, 0}, 3, board,
                   eBuildingType::temple, 4, 4) {
    setEnabled(true);
}
