#include "esculpturestudio.h"

#include "textures/egametextures.h"

eSculptureStudio::eSculptureStudio(eGameBoard& board) :
    eProcessingBuilding(board,
                        &eBuildingTextures::fSculptureStudio,
                        -3.73, -4.48,
                        &eBuildingTextures::fSculptureStudioOverlay,
                        eBuildingType::sculptureStudio, 2, 2, 12,
                        eResourceType::bronze,
                        eResourceType::sculpture, 1, 10) {
    eGameTextures::loadSculptureStudio();
}
