#include "efertiletodry.h"

#include "engine/etile.h"

eFertileToDryId eFertileToDry::get(eTile* const tile,
                                   const eWorldDirection dir) {
    if(!tile) return eFertileToDryId::none;

    const auto terr = tile->terrain();

    bool tl;
    bool tr;
    bool br;
    bool bl;
    bool t;
    bool r;
    bool b;
    bool l;
    tile->neighboursWithTerrain(terr, tl, tr, br, bl, t, r, b, l, dir);

    eFertileToDryId result;
    if(tl || tr || bl || br || t || l || r || b) {
        result = eFertileToDryId::somewhere;
    } else {
        result = eFertileToDryId::none;
    }

    return result;
}
