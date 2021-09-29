#include "etemplebuilding.h"

#include "textures/egametextures.h"

eTempleBuilding::eTempleBuilding(const int id, eGameBoard& board) :
    eBuilding(board, eBuildingType::temple, 4, 4),
    mId(id) {

}

std::shared_ptr<eTexture>
eTempleBuilding::getTexture(const eTileSize size) const {
    const int sizeId = static_cast<int>(size);
    const auto& blds = eGameTextures::buildings()[sizeId];
    return blds.fSanctuary[mId].getTexture(2);
}
