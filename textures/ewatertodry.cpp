#include "ewatertodry.h"

#include "engine/etile.h"

eWaterToDryId eWaterToDry::get(eTile* const tile) {
    if(!tile) return eWaterToDryId::none;

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

    eWaterToDryId result;
    if(tl && tr && br && bl) {
        result = eWaterToDryId::all;
    }

    else if(tl && bl && br) {
        result = eWaterToDryId::topLeft_bottomLeft_bottomRight;
    } else if(bl && tl && tr) {
        result = eWaterToDryId::bottomLeft_topLeft_topRight;
    } else if(tl && tr && br) {
        result = eWaterToDryId::topLeft_topRight_bottomRight;
    } else if(tr && br && bl) {
        result = eWaterToDryId::topRight_bottomRight_bottomLeft;
    }

    else if(bl && br && t) {
        result = eWaterToDryId::top_bottomLeft_bottomRight;
    } else if(tr && br && l) {
        result = eWaterToDryId::left_topRight_bottomRight;
    } else if(tl && tr && b) {
        result = eWaterToDryId::bottom_topLeft_topRight;
    } else if(tl && bl && r) {
        result = eWaterToDryId::right_bottomLeft_topLeft;
    }

    else if(bl && br) {
        result = eWaterToDryId::bottomLeft_bottomRight;
    } else if(tr && br) {
        result = eWaterToDryId::topRight_bottomRight;
    } else if(tl && tr) {
        result = eWaterToDryId::topLeft_topRight;
    } else if(tl && bl) {
        result = eWaterToDryId::bottomLeft_topLeft;
    } else if(bl && tr) {
        result = eWaterToDryId::bottomLeft_topRight;
    } else if(tl && br) {
        result = eWaterToDryId::topLeft_bottomRight;
    }

    else if(t && r && bl) {
        result = eWaterToDryId::top_right_bottomLeft;
    } else if(b && r && tl) {
        result = eWaterToDryId::bottom_right_topLeft;
    } else if(b && l && tr) {
        result = eWaterToDryId::bottom_left_topRight;
    } else if(l && t && br) {
        result = eWaterToDryId::left_top_bottomRight;
    }

    else if(t && bl) {
        result = eWaterToDryId::top_bottomLeft;
    } else if(r && bl) {
        result = eWaterToDryId::right_bottomLeft;
    } else if(r && tl) {
        result = eWaterToDryId::right_topLeft;
    } else if(b && tl) {
        result = eWaterToDryId::bottom_topLeft;
    } else if(b && tr) {
        result = eWaterToDryId::bottom_topRight;
    } else if(l && tr) {
        result = eWaterToDryId::left_topRight;
    } else if(l && br) {
        result = eWaterToDryId::left_bottomRight;
    } else if(t && br) {
        result = eWaterToDryId::top_bottomRight;
    }

    else if(br) {
        result = eWaterToDryId::bottomRight;
    } else if(tr) {
        result = eWaterToDryId::topRight;
    } else if(tl) {
        result = eWaterToDryId::topLeft;
    } else if(bl) {
        result = eWaterToDryId::bottomLeft;
    }

    else if(t && b && l && r) {
        result = eWaterToDryId::top_right_bottom_left;
    }

    else if(b && l && r) {
        result = eWaterToDryId::right_bottom_left;
    } else if(b && l && t) {
        result = eWaterToDryId::bottom_left_top;
    } else if(t && r && b) {
        result = eWaterToDryId::top_right_bottom;
    } else if(l && t && r) {
        result = eWaterToDryId::left_top_right;
    }

    else if(l && r) {
        result = eWaterToDryId::left_right;
    } else if(t && b) {
        result = eWaterToDryId::top_bottom;
    } else if(t && l) {
        result = eWaterToDryId::top_left;
    } else if(t && r) {
        result = eWaterToDryId::top_right;
    } else if(b && r) {
        result = eWaterToDryId::right_bottom;
    } else if(l && b) {
        result = eWaterToDryId::left_bottom;
    }

    else if(t) {
        result = eWaterToDryId::top;
    } else if(r) {
        result = eWaterToDryId::right;
    } else if(b) {
        result = eWaterToDryId::bottom;
    } else if(l) {
        result = eWaterToDryId::left;
    } else {
        result = eWaterToDryId::none;
    }

    return result;
}
