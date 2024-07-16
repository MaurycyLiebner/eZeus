#include "earmsvendor.h"

#include "textures/egametextures.h"

eArmsVendor::eArmsVendor(eGameBoard& board) :
    eVendor(board,
            eResourceType::armor, eProvide::arms,
            &eBuildingTextures::fArmsVendor,
            -1.86, -2.39, &eBuildingTextures::fArmsVendorOverlay,
            0.14, -2.39, &eBuildingTextures::fArmsVendorOverlay2,
            eBuildingType::armsVendor, 2, 2, 4) {
    eGameTextures::loadArmsVendor();
    setResMult(1);
    setMaxRes(8);
}
