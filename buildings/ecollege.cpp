#include "ecollege.h"

#include "textures/egametextures.h"

eCollege::eCollege(eGameBoard& board) :
    ePatrolSourceBuilding(board,
                          &eBuildingTextures::fCollege,
                          -2.7, -4.38,
                          &eBuildingTextures::fCollegeOverlay,
                          {{eCharacterType::philosopher,
                            eBuildingType::podium}},
                          eBuildingType::college, 3, 3, 12) {
    eGameTextures::loadCollege();
}
