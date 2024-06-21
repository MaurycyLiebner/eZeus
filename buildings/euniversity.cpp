#include "euniversity.h"

#include "textures/egametextures.h"

eUniversity::eUniversity(eGameBoard& board) :
    ePatrolSourceBuilding(board,
                          &eBuildingTextures::fUniversity,
                          -3.25, -4.00,
                          &eBuildingTextures::fUniversityOverlay,
                          {{eCharacterType::astronomer,
                            eBuildingType::observatory},
                           {eCharacterType::curator,
                            eBuildingType::museum}},
                          eBuildingType::university, 3, 3, 12) {
    eGameTextures::loadUniversity();
}
