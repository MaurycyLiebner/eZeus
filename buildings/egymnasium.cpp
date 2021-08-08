#include "egymnasium.h"

#include "characters/egymnast.h"
#include "textures/egametextures.h"

eGymnasium::eGymnasium(eGameBoard& board) :
    ePatrolBuilding(board,
                    &eBuildingTextures::fGymnasium,
                    -2.57, -4.57,
                    &eBuildingTextures::fGymnasiumOverlay,
                    [this]() { return new eGymnast(getBoard()); },
                    eBuildingType::gymnasium, 3, 3) {

}
