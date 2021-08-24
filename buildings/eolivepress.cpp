#include "eolivepress.h"

eOlivePress::eOlivePress(eGameBoard& board) :
    eProcessingBuilding(board,
                        &eBuildingTextures::fOlivePress,
                        -3.65, -3.75,
                        &eBuildingTextures::fOlivePressOverlay,
                        eBuildingType::olivePress, 2, 2,
                        eResourceType::olives,
                        eResourceType::oliveOil, 1, 2) {

}
