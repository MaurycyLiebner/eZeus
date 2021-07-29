#include "estonestodry.h"

eStonesToDryId eStonesToDry::get(eTile* const tile) {
    const auto terr = tile->terrain();

    const auto bt = tile->bottom();
    if(!bt) return eStonesToDryId::small;

    const auto blt = tile->bottomLeft();
    const auto brt = tile->bottomRight();

    if(blt->terrain() != terr) return eStonesToDryId::small;
    if(brt->terrain() != terr) return eStonesToDryId::small;
    return eStonesToDryId::large;
}
