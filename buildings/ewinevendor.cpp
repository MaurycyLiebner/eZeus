#include "ewinevendor.h"

#include "textures/egametextures.h"

eWineVendor::eWineVendor(eGameBoard& board) :
    eVendor(board,
            eResourceType::wine, eProvide::wine,
            &eBuildingTextures::fWineVendor,
            -2.15, -2.35, &eBuildingTextures::fWineVendorOverlay,
            0.35, -2.55, &eBuildingTextures::fWineVendorOverlay2,
            eBuildingType::wineVendor, 2, 2, 4) {
    eGameTextures::loadWineVendorBuilding();
}
