#include "efoodvendor.h"

#include "characters/efoodvendorchar.h"

#include "textures/egametextures.h"

eFoodVendor::eFoodVendor(eGameBoard& board) :
    ePatrolBuilding(board,
                    &eBuildingTextures::fFoodVendor,
                    0, 0, nullptr,
                    [this]() { return e::make_shared<eFoodVendorChar>(getBoard()); },
                    eBuildingType::foodVendor, 2, 2, 4) {

}

std::vector<eOverlay> eFoodVendor::getOverlays(const eTileSize size) const {
    const int sizeId = static_cast<int>(size);
    const auto& texs = eGameTextures::buildings();
    eOverlay o;
    o.fTex = texs[sizeId].fFoodVendorOverlay;
    o.fX = -2.35;
    o.fY = -2.5;
    return std::vector<eOverlay>({o});
}
