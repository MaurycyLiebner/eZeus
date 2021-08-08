#ifndef ETERRAIN_H
#define ETERRAIN_H


enum class eTerrain {
    dry = 1 << 0,
    beach = 1 << 1,
    water = 1 << 2,
    fertile = 1 << 3,
    forest = 1 << 4,

    flatStones = 1 << 5,
    bronze = 1 << 6,
    silver = 1 << 7,
    tallStones = 1 << 8,
    tinyStones = 1 << 9,

    dryBased = dry |
               fertile |
               forest |

               flatStones |
               bronze |
               silver |
               tallStones |
               tinyStones,

    buildable = dry | beach | fertile
};

inline eTerrain operator|(const eTerrain a, const eTerrain b) {
    return static_cast<eTerrain>(static_cast<int>(a) | static_cast<int>(b));
}

inline eTerrain operator&(const eTerrain a, const eTerrain b) {
    return static_cast<eTerrain>(static_cast<int>(a) & static_cast<int>(b));
}

namespace eTerrainTools {
    double speed(const eTerrain t);
}

#endif // ETERRAIN_H
