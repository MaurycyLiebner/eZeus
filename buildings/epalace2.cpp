#include "epalace2.h"

#include "characters/egymnast.h"
#include "characters/actions/epatrolaction.h"
#include "textures/egametextures.h"

ePalace2W::ePalace2W(eGameBoard& board) :
    eBuilding(board, eBuildingType::palace2, 4, 4),
    mTextures(eGameTextures::buildings()) {

}

std::shared_ptr<eTexture> ePalace2W::getTexture(const eTileSize size) const {
    const int sizeId = static_cast<int>(size);
    return mTextures[sizeId].fPalace2W;
}

ePalace2H::ePalace2H(eGameBoard& board) :
    eBuilding(board, eBuildingType::palace2, 4, 4),
    mTextures(eGameTextures::buildings()) {

}

std::shared_ptr<eTexture> ePalace2H::getTexture(const eTileSize size) const {
    const int sizeId = static_cast<int>(size);
    return mTextures[sizeId].fPalace2H;
}
