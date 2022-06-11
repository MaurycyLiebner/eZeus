#include "efoundry.h"

#include "characters/ebronzeminer.h"
#include "textures/egametextures.h"

eFoundry::eFoundry(eGameBoard& board) :
    eResourceCollectBuilding(board,
                             &eBuildingTextures::fFoundry,
                             -3.80, -3.78,
                             &eBuildingTextures::fFoundryOverlay,
                             2, 1.0, -2.0,
                             [this]() { return e::make_shared<eBronzeMiner>(getBoard()); },
                             eBuildingType::foundry,
                             [](eTileBase* const t) {
                                return t->terrain() == eTerrain::copper;
                             },
                             [](eTile* const t) {
                                t->setTerrain(eTerrain::dry);
                             }, 2, 2, 15,
                             eResourceType::bronze) {
    setRawCountCollect(4);
}
