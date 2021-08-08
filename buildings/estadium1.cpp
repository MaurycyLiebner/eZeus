#include "estadium1.h"

#include "characters/egymnast.h"
#include "characters/actions/epatrolaction.h"
#include "textures/egametextures.h"

eStadium1W::eStadium1W(eGameBoard& board) :
    eBuilding(board, eBuildingType::stadium1, 5, 5),
    mTextures(eGameTextures::buildings()) {

}

eTexture eStadium1W::getTexture(const eTileSize size) const {
    const int sizeId = static_cast<int>(size);
    return mTextures[sizeId].fStadium1W;
}

eStadium1H::eStadium1H(eGameBoard& board) :
    eBuilding(board, eBuildingType::stadium1, 5, 5),
    mTextures(eGameTextures::buildings()) {

}

eTexture eStadium1H::getTexture(const eTileSize size) const {
    const int sizeId = static_cast<int>(size);
    return mTextures[sizeId].fStadium1H;
}
