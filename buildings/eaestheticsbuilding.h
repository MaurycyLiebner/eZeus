#ifndef EAESTHETICSBUILDING_H
#define EAESTHETICSBUILDING_H

#include "ebuilding.h"

#include "textures/ebuildingtextures.h"

class eAestheticsBuilding : public eBuilding {
public:
    using eBaseTex = std::shared_ptr<eTexture> eBuildingTextures::*;
    eAestheticsBuilding(eGameBoard& board,
                        const eBaseTex baseTex,
                        const eBuildingType type,
                        const int sw, const int sh);

    std::shared_ptr<eTexture> getTexture(const eTileSize size) const;
private:
    const eBaseTex mTexture;
};

class eBench : public eAestheticsBuilding {
public:
    eBench(eGameBoard& board);
};

class eFlowerGarden : public eAestheticsBuilding {
public:
    eFlowerGarden(eGameBoard& board);
};

class eGazebo : public eAestheticsBuilding {
public:
    eGazebo(eGameBoard& board);
};

class eHedgeMaze : public eAestheticsBuilding {
public:
    eHedgeMaze(eGameBoard& board);
};

class eFishPond : public eAestheticsBuilding {
public:
    eFishPond(eGameBoard& board);
};

#endif // EAESTHETICSBUILDING_H
