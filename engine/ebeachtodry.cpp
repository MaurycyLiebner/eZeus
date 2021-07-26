#include "ebeachtodry.h"

#include "etile.h"

eBeachToDryId eBeachToDry::get(eTile* const tile) {
    if(!tile) return eBeachToDryId::none;

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

    eBeachToDryId result;
    if(bl && br) {
        result = eBeachToDryId::bottomLeftAndBottomRight;
    } else if(tr && br) {
        result = eBeachToDryId::topRightAndBottomRight;
    } else if(tl && tr) {
        result = eBeachToDryId::topLeftAndTopRight;
    } else if(tl && bl) {
        result = eBeachToDryId::topLeftAndBottomLeft;
    } else if(br) {
        result = eBeachToDryId::bottomRight;
    } else if(tr) {
        result = eBeachToDryId::topRight;
    } else if(tl) {
        result = eBeachToDryId::topLeft;
    } else if(bl) {
        result = eBeachToDryId::bottomLeft;
    } else if(t) {
        result = eBeachToDryId::top;
    } else if(r) {
        result = eBeachToDryId::right;
    } else if(b) {
        result = eBeachToDryId::bottom;
    } else if(l) {
        result = eBeachToDryId::left;
    } else {
        result = eBeachToDryId::none;
    }

    return result;
}
