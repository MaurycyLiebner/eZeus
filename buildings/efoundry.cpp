#include "efoundry.h"

#include "characters/ebronzeminer.h"
#include "textures/egametextures.h"


bool hasCopper(eTileBase* const t) {
    return t->terrain() == eTerrain::copper;
}

eFoundry::eFoundry(eGameBoard& board) :
    eResourceCollectBuilding(board,
                             &eBuildingTextures::fFoundry,
                             -3.80, -3.78,
                             &eBuildingTextures::fFoundryOverlay,
                             2, 1.0, -2.0,
                             [this]() { return e::make_shared<eBronzeMiner>(getBoard()); },
                             eBuildingType::foundry,
                             hasCopper, nullptr, 2, 2, 15,
                             eResourceType::bronze) {
    setRawCountCollect(4);
}
