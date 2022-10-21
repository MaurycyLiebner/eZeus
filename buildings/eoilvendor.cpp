#include "eoilvendor.h"

eOilVendor::eOilVendor(eGameBoard& board) :
    eVendor(board,
            eResourceType::oliveOil, eProvide::oil,
            &eBuildingTextures::fOilVendor,
            -2.56, -3.05, &eBuildingTextures::fOilVendorOverlay,
            -0.74, -2.45, &eBuildingTextures::fOilVendorOverlay2,
            eBuildingType::oilVendor, 2, 2, 4) {}
