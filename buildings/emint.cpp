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
                             eHasResourceObject::sCreate(eHasResourceObjectType::silver),
                             2, 2, 15, eResourceType::silver) {
    eGameTextures::loadMint();
    setRawCountCollect(4);
}
