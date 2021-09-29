#include "etemplealtarbuilding.h"

#include "textures/egametextures.h"

eTempleAltarBuilding::eTempleAltarBuilding(eGameBoard& board) :
    eSanctBuilding(board, eBuildingType::templeAltar, 2, 2) {

}

std::shared_ptr<eTexture>
eTempleAltarBuilding::getTexture(const eTileSize size) const {
    const int p = progress();
    if(p <= 0) return nullptr;
    const int sizeId = static_cast<int>(size);
    const auto& blds = eGameTextures::buildings()[sizeId];
    return blds.fSanctuaryAltar;
}
