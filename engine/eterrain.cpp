#include "eterrain.h"

double eTerrainTools::speed(const eTerrain t) {
    switch(t) {
        case eTerrain::dry: return 1;
        case eTerrain::beach: return 1;
        case eTerrain::water: return 0;
        case eTerrain::fertile: return 1;
        case eTerrain::forest: return 0.75;
        case eTerrain::choppedForest: return 1;

        case eTerrain::flatStones: return 0;
        case eTerrain::copper: return 0;
        case eTerrain::silver: return 0;
        case eTerrain::tallStones: return 0;
        case eTerrain::marble: return 1;

        default: return 0;
    }
}
