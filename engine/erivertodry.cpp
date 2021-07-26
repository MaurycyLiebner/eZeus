#include "erivertodry.h"

#include "etile.h"

eRiverToDryId eRiverToDry::get(eTile* const tile) {
    if(!tile) return eRiverToDryId::none;

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

    eRiverToDryId result;
    if(tl && tr && br && bl) {
        result = eRiverToDryId::all;
    }

    else if(tl && bl && br) {
        result = eRiverToDryId::topLeft_bottomLeft_bottomRight;
    } else if(bl && tl && tr) {
        result = eRiverToDryId::bottomLeft_topLeft_topRight;
    } else if(tl && tr && br) {
        result = eRiverToDryId::topLeft_topRight_bottomRight;
    } else if(tr && br && bl) {
        result = eRiverToDryId::topRight_bottomRight_bottomLeft;
    }

    else if(bl && br && t) {
        result = eRiverToDryId::top_bottomLeft_bottomRight;
    } else if(tr && br && l) {
        result = eRiverToDryId::left_topRight_bottomRight;
    } else if(tl && tr && b) {
        result = eRiverToDryId::bottom_topLeft_topRight;
    } else if(tl && bl && r) {
        result = eRiverToDryId::right_bottomLeft_topLeft;
    }

    else if(bl && br) {
        result = eRiverToDryId::bottomLeft_bottomRight;
    } else if(tr && br) {
        result = eRiverToDryId::topRight_bottomRight;
    } else if(tl && tr) {
        result = eRiverToDryId::topLeft_topRight;
    } else if(tl && bl) {
        result = eRiverToDryId::bottomLeft_topLeft;
    } else if(bl && tr) {
        result = eRiverToDryId::bottomLeft_topRight;
    } else if(tl && br) {
        result = eRiverToDryId::topLeft_bottomRight;
    }

    else if(t && r && bl) {
        result = eRiverToDryId::top_right_bottomLeft;
    } else if(b && r && tl) {
        result = eRiverToDryId::bottom_right_topLeft;
    } else if(b && l && tr) {
        result = eRiverToDryId::bottom_left_topRight;
    } else if(l && t && br) {
        result = eRiverToDryId::left_top_bottomRight;
    }

    else if(t && bl) {
        result = eRiverToDryId::top_bottomLeft;
    } else if(r && bl) {
        result = eRiverToDryId::right_bottomLeft;
    } else if(r && tl) {
        result = eRiverToDryId::right_topLeft;
    } else if(b && tl) {
        result = eRiverToDryId::bottom_topLeft;
    } else if(b && tr) {
        result = eRiverToDryId::bottom_topRight;
    } else if(l && tr) {
        result = eRiverToDryId::left_topRight;
    } else if(l && br) {
        result = eRiverToDryId::left_bottomRight;
    } else if(t && br) {
        result = eRiverToDryId::top_bottomRight;
    }

    else if(br) {
        result = eRiverToDryId::bottomRight;
    } else if(tr) {
        result = eRiverToDryId::topRight;
    } else if(tl) {
        result = eRiverToDryId::topLeft;
    } else if(bl) {
        result = eRiverToDryId::bottomLeft;
    }

    else if(t && b && l && r) {
        result = eRiverToDryId::top_right_bottom_left;
    }

    else if(b && l && r) {
        result = eRiverToDryId::right_bottom_left;
    } else if(b && l && t) {
        result = eRiverToDryId::bottom_left_top;
    } else if(t && r && b) {
        result = eRiverToDryId::top_right_bottom;
    } else if(l && t && r) {
        result = eRiverToDryId::left_top_right;
    }

    else if(l && r) {
        result = eRiverToDryId::left_right;
    } else if(t && b) {
        result = eRiverToDryId::top_bottom;
    } else if(t && l) {
        result = eRiverToDryId::top_left;
    } else if(t && r) {
        result = eRiverToDryId::top_right;
    } else if(b && r) {
        result = eRiverToDryId::right_bottom;
    } else if(l && b) {
        result = eRiverToDryId::left_bottom;
    }

    else if(t) {
        result = eRiverToDryId::top;
    } else if(r) {
        result = eRiverToDryId::right;
    } else if(b) {
        result = eRiverToDryId::bottom;
    } else if(l) {
        result = eRiverToDryId::left;
    } else {
        result = eRiverToDryId::none;
    }

    return result;
}
