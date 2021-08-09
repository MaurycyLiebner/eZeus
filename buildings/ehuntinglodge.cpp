#include "ehuntinglodge.h"

#include "characters/ehunter.h"
#include "textures/egametextures.h"

eHuntingLodge::eHuntingLodge(eGameBoard& board) :
    eBuilding(board, eBuildingType::huntingLodge, 2, 2) {

}
