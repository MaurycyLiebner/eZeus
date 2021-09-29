#include "etempletilebuilding.h"

#include "textures/egametextures.h"

eTempleTileBuilding::eTempleTileBuilding(const int id, eGameBoard& board) :
    eBuilding(board, eBuildingType::templeTile, 1, 1),
    mId(id) {

}

std::shared_ptr<eTexture>
eTempleTileBuilding::getTexture(const eTileSize size) const {
    const int sizeId = static_cast<int>(size);
    const auto& blds = eGameTextures::buildings()[sizeId];
    const auto& coll = blds.fSanctuaryTiles;
    return coll.getTexture(mId);
}
