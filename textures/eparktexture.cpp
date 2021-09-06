#include "eparktexture.h"

#include "evaryingsizetex.h"
#include "buildings/ebuilding.h"

void eParkTexture::get(eTile* const tile,
                       int& futureDim,
                       int& drawDim) {
    const auto checker = [](eTile* const t) {
        return t->underBuildingType() == eBuildingType::park;
    };
    eVaryingSizeTex::get(tile, checker, futureDim, drawDim);
}
