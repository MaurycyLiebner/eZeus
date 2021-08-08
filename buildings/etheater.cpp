#include "etheater.h"

#include "characters/egymnast.h"
#include "characters/actions/epatrolaction.h"
#include "textures/egametextures.h"

eTheater::eTheater(eGameBoard& board) :
    eBuilding(board, eBuildingType::theater, 5, 5),
    mTextures(eGameTextures::buildings()) {

}

eTexture eTheater::getTexture(const eTileSize size) const {
    const int sizeId = static_cast<int>(size);
    return mTextures[sizeId].fTheater;
}
