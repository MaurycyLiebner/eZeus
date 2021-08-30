#ifndef EROAD_H
#define EROAD_H

#include "ebuilding.h"
#include "textures/ebuildingtextures.h"

class eRoad : public eBuilding {
public:
    eRoad(eGameBoard& board);

    std::shared_ptr<eTexture> getTexture(const eTileSize size) const;
private:
    const std::vector<eBuildingTextures>& mTextures;
};

#endif // EROAD_H
