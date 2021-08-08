#include "estadium2.h"

#include "characters/egymnast.h"
#include "characters/actions/epatrolaction.h"
#include "textures/egametextures.h"

eStadium2W::eStadium2W(eGameBoard& board) :
    eBuilding(board, eBuildingType::stadium2, 5, 5),
    mTextures(eGameTextures::buildings()) {

}

eTexture eStadium2W::getTexture(const eTileSize size) const {
    const int sizeId = static_cast<int>(size);
    return mTextures[sizeId].fStadium2W;
}


eStadium2H::eStadium2H(eGameBoard& board) :
    eBuilding(board, eBuildingType::stadium2, 5, 5),
    mTextures(eGameTextures::buildings()) {

}

eTexture eStadium2H::getTexture(const eTileSize size) const {
    const int sizeId = static_cast<int>(size);
    return mTextures[sizeId].fStadium2H;
}
