#include "earmsvendor.h"

#include "characters/earmsvendorchar.h"

eArmsVendor::eArmsVendor(const stdsptr<eCommonAgora>& agora,
                         eGameBoard& board) :
    eVendor(board, agora,
            eResourceType::armor, eProvide::arms,
            &eBuildingTextures::fArmsVendor,
            -1.86, -2.39, &eBuildingTextures::fArmsVendorOverlay,
            0.14, -2.39, &eBuildingTextures::fArmsVendorOverlay2,
            eBuildingType::armsVendor, 2, 2, 4) {}
