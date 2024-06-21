#include "edramaschool.h"

#include "textures/egametextures.h"

eDramaSchool::eDramaSchool(eGameBoard& board) :
    ePatrolSourceBuilding(board,
                          &eBuildingTextures::fDramaSchool,
                          -3.08, -4.51,
                          &eBuildingTextures::fDramaSchoolOverlay,
                          {{eCharacterType::actor,
                            eBuildingType::theater}},
                          eBuildingType::dramaSchool, 3, 3, 10) {
    eGameTextures::loadDramaSchool();
}
