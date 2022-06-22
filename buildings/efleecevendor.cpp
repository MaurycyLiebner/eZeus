#include "efleecevendor.h"

#include "characters/efleecevendorchar.h"

eFleeceVendor::eFleeceVendor(const stdsptr<eCommonAgora>& agora,
                             eGameBoard& board) :
    eVendor(board, agora,
            eResourceType::fleece, eProvide::fleece,
            &eBuildingTextures::fFleeceVendor,
            -2.00, -2.42, &eBuildingTextures::fFleeceVendorOverlay,
            -0.50, -2.42, &eBuildingTextures::fFleeceVendorOverlay2,
            eBuildingType::fleeceVendor, 2, 2, 4) {}
