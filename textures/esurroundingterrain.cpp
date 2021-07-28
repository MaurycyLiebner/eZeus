#include "esurroundingterrain.h"

eSurroundingTerrain::eSurroundingTerrain(eTile* const tile) {
    tile->surroundingTerrain(mTL, mTR, mBR, mBL, mT, mR, mB, mL);
}

bool eSurroundingTerrain::operator()(const eTerrain t, const eTerrain tr,
                                     const eTerrain r, const eTerrain br,
                                     const eTerrain b, const eTerrain bl,
                                     const eTerrain l, const eTerrain tl) {
    if(!static_cast<int>(t & mT)) return false;
    if(!static_cast<int>(tr & mTR)) return false;
    if(!static_cast<int>(r & mR)) return false;
    if(!static_cast<int>(br & mBR)) return false;
    if(!static_cast<int>(b & mB)) return false;
    if(!static_cast<int>(bl & mBL)) return false;
    if(!static_cast<int>(l & mL)) return false;
    if(!static_cast<int>(tl & mTL)) return false;
    return true;
}
