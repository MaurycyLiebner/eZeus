#include "einventorsworkshop.h"

#include "textures/egametextures.h"

eInventorsWorkshop::eInventorsWorkshop(eGameBoard& board) :
    ePatrolSourceBuilding(board,
                          &eBuildingTextures::fInventorsWorkshop,
                          -1.08, -4.61,
                          &eBuildingTextures::fInventorsWorkshopOverlay,
                          {{eCharacterType::inventor,
                            eBuildingType::laboratory}},
                          eBuildingType::inventorsWorkshop, 3, 3, 12) {
    eGameTextures::loadInventorsWorkshop();
}
