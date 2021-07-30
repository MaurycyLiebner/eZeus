#ifndef EROAD_H
#define EROAD_H

#include "ebuilding.h"
#include "textures/ebuildingtextures.h"

class eRoad : public eBuilding {
public:
    eRoad(std::vector<eBuildingTextures>& texs);

    eTexture getTexture(const eTileSize size) const;
private:
    std::vector<eBuildingTextures>& mTextures;
};

#endif // EROAD_H
