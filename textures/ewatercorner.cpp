#include "ewatercorner.h"

#include "engine/etile.h"

#include <algorithm>

bool eWaterCorner::detect(eTile* const tile) {
    const auto tt = tile->terrain();
    if(tt != eTerrain::water) return false;
    std::vector<eTerrain> neighTypes;
    tile->neighbourTerrainTypes(neighTypes);
    const auto waterIt = std::find(neighTypes.begin(), neighTypes.end(),
                                   eTerrain::water);
    if(waterIt == neighTypes.end()) return false;
    const auto beachIt = std::find(neighTypes.begin(), neighTypes.end(),
                                   eTerrain::beach);
    if(beachIt == neighTypes.end()) return false;
    const auto dryIt = std::find(neighTypes.begin(), neighTypes.end(),
                                 eTerrain::dry);
    if(dryIt == neighTypes.end()) return false;
    return true;
}

int eWaterCorner::get(eTile* const tile) {
    eTerrain tl;
    eTerrain tr;
    eTerrain br;
    eTerrain bl;

    eTerrain t;
    eTerrain r;
    eTerrain b;
    eTerrain l;

    tile->neighbourTerrain(tl, tr, br, bl,
                           t, r, b, l);

    const auto dry = eTerrain::dry;
    const auto water = eTerrain::water;
    const auto beach = eTerrain::beach;

    int id = 0;
    if(l == dry &&
       tr == water &&
       b == beach &&
       br == water &&
       t == water &&
       r == water) {
        id = 0;
    } else if(l == beach &&
              b == dry &&
              tr == water) {
        id = 1;
    } else if(tl == dry &&
              b == beach &&
              r == water) {
        id = 2;
    } else if(br == dry &&
              l == beach &&
              t == water) {
        id = 3;
    } else if(t == water &&
              l == dry &&
              br == beach) {
        id = 4;
    } else if(tl == beach &&
              b == dry &&
              r == water) {
        id = 5;
    } else if(br == water &&
              t == dry &&
              l == beach) {
        id = 6;
    } else if(t == beach &&
              l == dry &&
              br == water) {
        id = 7;
    } else if(tr == dry &&
              l == beach &&
              b == water) {
        id = 8;
    } else if(bl == dry &&
              t == beach &&
              r == water) {
        id = 9;
    } else if(t == dry &&
              bl == beach &&
              r == water) {
        id = 10;
    } else if(l == dry &&
              tr == beach &&
              b == water) {
        id = 11;
    } else if(bl == water &&
              l == water &&
              b == water &&
              t == beach &&
              r == dry) {
        id = 12;
    } else if(bl == water &&
              t == dry &&
              r == beach) {
        id = 13;
    } else if(l == water &&
              t == beach &&
              br == dry) {
        id = 14;
    } else if(tl == dry &&
              b == water &&
              r == beach) {
        id = 15;
    } else if(tl == beach &&
              r == dry &&
              b == water) {
        id = 16;
    } else if(l == water &&
              t == dry &&
              br == beach) {
        id = 17;
    } else if(tl == water &&
              b == dry &&
              r == beach) {
        id = 18;
    } else if(tl == water &&
              r == dry &&
              b == beach) {
        id = 19;
    } else if(bl == dry &&
              t == water &&
              r == beach) {
        id = 20;
    } else if(tr == dry &&
              l == water &&
              b == beach) {
        id = 21;
    } else if(tr == beach &&
              l == water &&
              b == dry) {
        id = 22;
    } else if(t == water &&
              bl == beach &&
              r == dry) {
        id = 23;
    }
    return id;
}
