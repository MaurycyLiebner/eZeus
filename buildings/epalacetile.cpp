#include "epalacetile.h"

#include "textures/egametextures.h"

ePalaceTile::ePalaceTile(eGameBoard& board, const bool other) :
    eBuilding(board, eBuildingType::palaceTile, 1, 1),
    mOther(other) {

}

std::shared_ptr<eTexture> ePalaceTile::getTexture(const eTileSize size) const {
    const int sizeId = static_cast<int>(size);
    const auto& texs = eGameTextures::buildings();
    const auto& coll = texs[sizeId].fPalaceTiles;
    const int id = mOther ? 1 : 0;
    return coll.getTexture(id);
}
