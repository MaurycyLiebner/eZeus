#include "epalacetile.h"

#include "textures/egametextures.h"

ePalaceTile::ePalaceTile(eGameBoard& board) :
    eBuilding(board, eBuildingType::palaceTile, 1, 1) {

}

std::shared_ptr<eTexture> ePalaceTile::getTexture(const eTileSize size) const {
    const int sizeId = static_cast<int>(size);
    const auto& texs = eGameTextures::buildings();
    return texs[sizeId].fPalaceTiles.getTexture(0);
}
