#include "ewinevendor.h"

#include "characters/ewinevendorchar.h"

eWineVendor::eWineVendor(const stdsptr<eCommonAgora>& agora,
                         eGameBoard& board) :
    eVendor(board, agora,
            eResourceType::wine, eProvide::wine,
            &eBuildingTextures::fWineVendor,
            -2.15, -2.35, &eBuildingTextures::fWineVendorOverlay,
            [this]() { return e::make_shared<eWineVendorChar>(getBoard()); },
            eBuildingType::wineVendor, 2, 2, 4) {}
