#include "efoodvendor.h"

eFoodVendor::eFoodVendor(const stdsptr<eAgoraBase>& agora,
                         eGameBoard& board) :
    eVendor(board, agora,
            eResourceType::food, eProvide::food,
            &eBuildingTextures::fFoodVendor,
            -2.41, -2.46, &eBuildingTextures::fFoodVendorOverlay,
            0.35, -1.94, &eBuildingTextures::fFoodVendorOverlay2,
            eBuildingType::foodVendor, 2, 2, 4) {}
