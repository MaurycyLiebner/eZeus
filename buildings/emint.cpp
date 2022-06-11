#include "emint.h"

#include "characters/esilverminer.h"
#include "textures/egametextures.h"

eMint::eMint(eGameBoard& board) :
    eResourceCollectBuilding(board,
                             &eBuildingTextures::fMint,
                             -3.73, -3.73,
                             &eBuildingTextures::fMintOverlay,
                             3, 0.5, -1.5,
                             [this]() { return e::make_shared<eSilverMiner>(getBoard()); },
                             eBuildingType::mint,
                             [](eTileBase* const t) {
                                return t->terrain() == eTerrain::silver;
                             },
                             [](eTile* const t) {
                                t->setTerrain(eTerrain::dry);
                             }, 2, 2, 15,
                             eResourceType::silver) {
    setRawCountCollect(4);
}
