#include "etemplealtarbuilding.h"

#include "textures/egametextures.h"

eTempleAltarBuilding::eTempleAltarBuilding(eGameBoard& board) :
    eBuilding(board, eBuildingType::templeAltar, 2, 2) {

}

std::shared_ptr<eTexture>
eTempleAltarBuilding::getTexture(const eTileSize size) const {
    const int sizeId = static_cast<int>(size);
    const auto& blds = eGameTextures::buildings()[sizeId];
    return blds.fSanctuaryAltar;
}
