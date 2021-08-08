#include "emint.h"

#include "characters/esilverminer.h"
#include "textures/egametextures.h"

eMint::eMint(eGameBoard& board) :
    eResourceCollectBuilding(board,
                             &eBuildingTextures::fMint,
                             -3.73, -3.73,
                             &eBuildingTextures::fMintOverlay,
                             [this]() { return new eSilverMiner(getBoard()); },
                             eBuildingType::mint,
                             [](eTile* const t) {
                                return t->terrain() == eTerrain::silver;
                             },
                             [](eTile* const t) {
                                t->setTerrain(eTerrain::flatStones);
                             }, 2, 2) {

}
