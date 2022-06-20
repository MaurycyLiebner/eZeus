#include "efleecevendor.h"

#include "characters/efleecevendorchar.h"

eFleeceVendor::eFleeceVendor(const stdsptr<eCommonAgora>& agora,
                             eGameBoard& board) :
    eVendor(board, agora,
            eResourceType::fleece, eProvide::fleece,
            &eBuildingTextures::fFleeceVendor,
            -2.00, -2.42, &eBuildingTextures::fFleeceVendorOverlay,
            [this]() { return e::make_shared<eFleeceVendorChar>(getBoard()); },
            eBuildingType::fleeceVendor, 2, 2, 4) {}
