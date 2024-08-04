#include "ewinery.h"

#include "textures/egametextures.h"
#include "enumbers.h"

eWinery::eWinery(eGameBoard& board) :
    eProcessingBuilding(board,
                        &eBuildingTextures::fWinery,
                        -2.2, -3.25,
                        &eBuildingTextures::fWineryOverlay,
                        eBuildingType::winery, 2, 2, 12,
                        eResourceType::grapes,
                        eResourceType::wine, 1,
                        eNumbers::sWineryProcessingPeriod) {
    eGameTextures::loadWinery();
}
