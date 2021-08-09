#include "etimbermill.h"

#include "characters/elumberjack.h"
#include "textures/egametextures.h"

eTimberMill::eTimberMill(eGameBoard& board) :
    eResourceCollectBuilding(board,
                             &eBuildingTextures::fTimberMill,
                             -3.65, -3.65,
                             &eBuildingTextures::fTimberMillOverlay,
                             [this]() { return new eLumberjack(getBoard()); },
                             eBuildingType::timberMill,
                             [](eTile* const t) {
                                return t->terrain() == eTerrain::forest;
                             },
                             [](eTile* const t) {
                                t->setTerrain(eTerrain::choppedForest);
                             }, 2, 2) {

}
