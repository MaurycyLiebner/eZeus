#include "efleecevendor.h"

#include "textures/egametextures.h"

eFleeceVendor::eFleeceVendor(eGameBoard& board) :
    eVendor(board,
            eResourceType::fleece, eProvide::fleece,
            &eBuildingTextures::fFleeceVendor,
            -2.00, -2.42, &eBuildingTextures::fFleeceVendorOverlay,
            -0.50, -2.42, &eBuildingTextures::fFleeceVendorOverlay2,
            eBuildingType::fleeceVendor, 2, 2, 4) {
    eGameTextures::loadFleeceVendor();
}
