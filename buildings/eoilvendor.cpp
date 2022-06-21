#include "eoilvendor.h"

#include "characters/eoilvendorchar.h"

eOilVendor::eOilVendor(const stdsptr<eCommonAgora>& agora,
                       eGameBoard& board) :
    eVendor(board, agora,
            eResourceType::oliveOil, eProvide::oil,
            &eBuildingTextures::fOilVendor,
            -2.56, -3.05, &eBuildingTextures::fOilVendorOverlay,
            -0.74, -2.45, &eBuildingTextures::fOilVendorOverlay2,
            [this]() { return e::make_shared<eOilVendorChar>(getBoard()); },
            eBuildingType::oilVendor, 2, 2, 4) {}
