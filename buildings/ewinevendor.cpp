#include "ewinevendor.h"

#include "characters/ewinevendorchar.h"

eWineVendor::eWineVendor(const stdsptr<eAgoraBase>& agora,
                         eGameBoard& board) :
    eVendor(board, agora,
            eResourceType::wine, eProvide::wine,
            &eBuildingTextures::fWineVendor,
            -2.15, -2.35, &eBuildingTextures::fWineVendorOverlay,
            0.35, -2.55, &eBuildingTextures::fWineVendorOverlay2,
            eBuildingType::wineVendor, 2, 2, 4) {}
