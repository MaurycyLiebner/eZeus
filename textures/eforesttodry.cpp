#include "eforesttodry.h"

#include "engine/etile.h"

eForestToDryId eForestToDry::get(eTile* const tile) {
    if(!tile) return eForestToDryId::none;

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

    eForestToDryId result;
    if(tl || tr || bl || br || t || l || r || b) {
        result = eForestToDryId::somewhere;
    } else {
        result = eForestToDryId::none;
    }

    return result;
}
