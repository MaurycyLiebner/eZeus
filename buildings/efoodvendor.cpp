#include "efoodvendor.h"

#include "characters/efoodvendorchar.h"

eFoodVendor::eFoodVendor(eGameBoard& board) :
    eVendor(board, eResourceType::food, eProvide::food,
            &eBuildingTextures::fFoodVendor,
            -2.41, -2.46, &eBuildingTextures::fFoodVendorOverlay,
            [this]() { return e::make_shared<eFoodVendorChar>(getBoard()); },
            eBuildingType::foodVendor, 2, 2, 4) {}
