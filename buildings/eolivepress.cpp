#include "eolivepress.h"

#include "textures/egametextures.h"
#include "enumbers.h"

eOlivePress::eOlivePress(eGameBoard& board) :
    eProcessingBuilding(board,
                        &eBuildingTextures::fOlivePress,
                        -3.65, -3.75,
                        &eBuildingTextures::fOlivePressOverlay,
                        eBuildingType::olivePress, 2, 2, 12,
                        eResourceType::olives,
                        eResourceType::oliveOil, 1,
                        eNumbers::sOlivePressProcessingPeriod) {
    eGameTextures::loadOlivePress();
}
