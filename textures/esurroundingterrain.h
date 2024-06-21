#ifndef ESURROUNDINGTERRAIN_H
#define ESURROUNDINGTERRAIN_H

#include "engine/etile.h"

struct eSurroundingTerrain {
    eSurroundingTerrain(eTile* const tile,
                        const eWorldDirection dir);

    bool operator()(const eTerrain t,
                    const eTerrain tr,
                    const eTerrain r,
                    const eTerrain br,
                    const eTerrain b,
                    const eTerrain bl,
                    const eTerrain l,
                    const eTerrain tl);
private:
    eTerrain mTL;
    eTerrain mTR;
    eTerrain mBR;
    eTerrain mBL;

    eTerrain mT;
    eTerrain mR;
    eTerrain mB;
    eTerrain mL;
};

#endif // ESURROUNDINGTERRAIN_H
