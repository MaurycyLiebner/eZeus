#include "epalace1.h"

#include "characters/egymnast.h"
#include "characters/actions/epatrolaction.h"
#include "textures/egametextures.h"

ePalace1W::ePalace1W(eGameBoard& board) :
    eBuilding(board, eBuildingType::palace1, 4, 4),
    mTextures(eGameTextures::buildings()) {

}

eTexture ePalace1W::getTexture(const eTileSize size) const {
    const int sizeId = static_cast<int>(size);
    return mTextures[sizeId].fPalace1W;
}

ePalace1H::ePalace1H(eGameBoard& board) :
    eBuilding(board, eBuildingType::palace1, 4, 4),
    mTextures(eGameTextures::buildings()) {

}

eTexture ePalace1H::getTexture(const eTileSize size) const {
    const int sizeId = static_cast<int>(size);
    return mTextures[sizeId].fPalace1H;
}
