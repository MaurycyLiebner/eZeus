#include "estonestodry.h"

#include "evaryingsizetex.h"

void eStonesToDry::get(eTile* const tile,
                       int& futureDim,
                       int& drawDim,
                       const eWorldDirection dir) {
    const auto terr = tile->terrain();
    const auto checker = [terr](eTile* const t) {
        return t->terrain() == terr;
    };
    eVaryingSizeTex::get(tile, checker, futureDim, drawDim, dir);
}
