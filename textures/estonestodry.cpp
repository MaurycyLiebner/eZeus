#include "estonestodry.h"

eStonesToDryId eStonesToDry::get(eTile* const tile) {
    const auto terr = tile->terrain();

    bool tl;
    bool tr;
    bool br;
    bool bl;
    bool t;
    bool r;
    bool b;
    bool l;
    tile->neighboursWithTerrain(terr, tl, tr, br, bl, t, r, b, l);

    eStonesToDryId result;
    if(tl || tr || bl || br || t || l || r || b) {
        result = eStonesToDryId::outer;
    } else {
        if(const auto brt = tile->top()) {
            const auto brti = get(brt);
            if(brti == eStonesToDryId::inner) {
                result = eStonesToDryId::doubleInner;
            } else {
                result = eStonesToDryId::inner;
            }
        } else {
            result = eStonesToDryId::outer;
        }
    }

    return result;
}
