#include "efoundry.h"

#include "characters/ebronzeminer.h"
#include "textures/egametextures.h"

eFoundry::eFoundry(eGameBoard& board) :
    eResourceCollectBuilding(board,
                             &eBuildingTextures::fFoundry,
                             -3.80, -3.78,
                             &eBuildingTextures::fFoundryOverlay,
                             [this]() { return new eBronzeMiner(getBoard()); },
                             eBuildingType::foundry,
                             [](eTile* const t) {
                                return t->terrain() == eTerrain::bronze;
                             },
                             [](eTile* const t) {
                                t->setTerrain(eTerrain::flatStones);
                             }, 2, 2) {

}
