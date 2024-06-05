#include "egymnasium.h"

#include "characters/egymnast.h"
#include "textures/egametextures.h"

eGymnasium::eGymnasium(eGameBoard& board) :
    ePatrolSourceBuilding(board,
                    &eBuildingTextures::fGymnasium,
                    -2.57, -4.57,
                    &eBuildingTextures::fGymnasiumOverlay,
                    {{eCharacterType::competitor, eBuildingType::stadium}},
                    eBuildingType::gymnasium, 3, 3, 7,
                    [this]() { return e::make_shared<eGymnast>(getBoard()); }) {
    eGameTextures::loadGymnasium();
}
