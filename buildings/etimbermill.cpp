#include "etimbermill.h"

#include "characters/elumberjack.h"
#include "engine/egameboard.h"

void transformForest(eTile* const t, eGameBoard& brd) {
    t->setTerrain(eTerrain::choppedForest);
    const auto action = [t]() {
        if(t->terrain() != eTerrain::choppedForest) return;
        t->setTerrain(eTerrain::forest);
    };
    const auto a = new ePlannedAction(false, 75000, action);
    brd.planAction(a);
}

bool hasForest(eTileBase* const t) {
    return t->terrain() == eTerrain::forest;
}

eTimberMill::eTimberMill(eGameBoard& board) :
    eResourceCollectBuilding(board,
                             &eBuildingTextures::fTimberMill,
                             -3.65, -3.65,
                             &eBuildingTextures::fTimberMillOverlay,
                             3, 0.9, -1.1,
                             [this]() { return e::make_shared<eLumberjack>(getBoard()); },
                             eBuildingType::timberMill,
                             hasForest, transformForest, 2, 2, 12,
                             eResourceType::wood) {
    setRawCountCollect(4);
}
