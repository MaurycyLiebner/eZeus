#include "efoodvendor.h"

#include "textures/egametextures.h"

eFoodVendor::eFoodVendor(eGameBoard& board) :
    eVendor(board,
            eResourceType::food, eProvide::food,
            &eBuildingTextures::fFoodVendor,
            -2.41, -2.46, &eBuildingTextures::fFoodVendorOverlay,
            0.35, -1.94, &eBuildingTextures::fFoodVendorOverlay2,
            eBuildingType::foodVendor, 2, 2, 4) {
    eGameTextures::loadFoodVendor();
}
