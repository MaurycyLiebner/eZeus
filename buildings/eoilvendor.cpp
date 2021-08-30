#include "eoilvendor.h"

#include "characters/eoilvendorchar.h"

eOilVendor::eOilVendor(eGameBoard& board) :
    eVendor(board, eResourceType::oliveOil, eProvide::oil,
            &eBuildingTextures::fOilVendor,
            -2.56, -3.05, &eBuildingTextures::fOilVendorOverlay,
            [this]() { return e::make_shared<eOilVendorChar>(getBoard()); },
            eBuildingType::oilVendor, 2, 2, 4) {}
