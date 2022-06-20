#include "earmsvendor.h"

#include "characters/earmsvendorchar.h"

eArmsVendor::eArmsVendor(const stdsptr<eCommonAgora>& agora,
                         eGameBoard& board) :
    eVendor(board, agora,
            eResourceType::armor, eProvide::arms,
            &eBuildingTextures::fArmsVendor,
            -1.86, -2.39, &eBuildingTextures::fArmsVendorOverlay,
            [this]() { return e::make_shared<eArmsVendorChar>(getBoard()); },
            eBuildingType::armsVendor, 2, 2, 4) {}
