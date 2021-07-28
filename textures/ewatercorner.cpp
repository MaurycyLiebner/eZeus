#include "ewatercorner.h"

#include "engine/etile.h"

#include <algorithm>

struct eTT {
    bool operator()(const eTerrain t,
                    const eTerrain tr,
                    const eTerrain r,
                    const eTerrain br,
                    const eTerrain b,
                    const eTerrain bl,
                    const eTerrain l,
                    const eTerrain tl) {
        if(t != fT) return false;
        if(tr != fTr) return false;
        if(r != fR) return false;
        if(br != fBr) return false;
        if(b != fB) return false;
        if(bl != fBl) return false;
        if(l != fL) return false;
        if(tl != fTl) return false;
        return true;
    }

    eTerrain fTl;
    eTerrain fTr;
    eTerrain fBr;
    eTerrain fBl;

    eTerrain fT;
    eTerrain fR;
    eTerrain fB;
    eTerrain fL;
};

int eWaterCorner::get(eTile* const tile) {
    const auto dry = eTerrain::dry;
    const auto water = eTerrain::water;
    const auto beach = eTerrain::beach;

    if(tile->terrain() != water) return -1;

    eTT tt;
    tile->neighbourTerrain(tt.fTl, tt.fTr, tt.fBr, tt.fBl,
                           tt.fT, tt.fR, tt.fB, tt.fL);

    int id = -1;
    if(tt(water, water, water, water, beach, beach, dry, water)) {
        id = 0;
    } else if(tt(water, water, water, water, dry, beach, beach, water)) {
        id = 1;
    } else if(tt(dry, water, water, water, beach, beach, dry, dry)) {
        id = 2;
    } else if(tt(water, water, dry, dry, dry, beach, beach, water)) {
        id = 3;
    } else if(tt(water, water, beach, beach, beach, beach, dry, water)) {
        id = 4;
    } else if(tt(beach, water, water, water, dry, beach, beach, beach)) {
        id = 5;
    } else if(tt(dry, water, water, water, water, water, beach, beach)) {
        id = 6;
    } else if(tt(beach, water, water, water, water, water, dry, beach)) {
        id = 7;
    } else if(tt(dry, dry, dry, water, water, water, beach, beach)) {
        id = 8;
    } else if(tt(beach, water, water, water, dry, dry, dry, beach)) {
        id = 9;
    } else if(tt(dry, water, water, water, beach, beach, beach, beach)) {
        id = 10;
    } else if(tt(beach, beach, beach, water, water, water, dry, beach)) {
        id = 11;
    } else if(tt(beach, beach, dry, water, water, water, water, water)) {
        id = 12;
    } else if(tt(dry, beach, beach, water, water, water, water, water)) {
        id = 13;
    } else if(tt(beach, beach, dry, dry, dry, water, water, water)) {
        id = 14;
    } else if(tt(dry, beach, beach, water, water, water, dry, dry)) {
        id = 15;
    } else if(tt(beach, beach, dry, water, water, water, beach, beach)) {
        id = 16;
    } else if(tt(dry, beach, beach, beach, beach, water, water, water)) {
        id = 17;
    } else if(tt(water, water, beach, beach, dry, water, water, water)) {
        id = 18;
    } else if(tt(water, water, dry, beach, beach, water, water, water)) {
        id = 19;
    } else if(tt(water, water, beach, beach, dry, dry, dry, water)) {
        id = 20;
    } else if(tt(dry, dry, dry, beach, beach, water, water, water)) {
        id = 21;
    } else if(tt(beach, beach, beach, beach, dry, water, water, water)) {
        id = 22;
    } else if(tt(water, water, dry, dry, beach, beach, beach, water)) {
        id = 23;
    }
    return id;
}
