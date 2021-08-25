#include "emint.h"

#include "characters/esilverminer.h"
#include "textures/egametextures.h"

eMint::eMint(eGameBoard& board) :
    eResourceCollectBuilding(board,
                             &eBuildingTextures::fMint,
                             -3.73, -3.73,
                             &eBuildingTextures::fMintOverlay,
                             [this]() { return e::make_shared<eSilverMiner>(getBoard()); },
                             eBuildingType::mint,
                             [](eTileBase* const t) {
                                return t->terrain() == eTerrain::silver;
                             },
                             [](eTile* const t) {
                                t->setTerrain(eTerrain::flatStones);
                             }, 2, 2,
                             eResourceType::silver) {

}
