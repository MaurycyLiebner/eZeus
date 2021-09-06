#ifndef EPARK_H
#define EPARK_H

#include "ebuilding.h"
#include "textures/ebuildingtextures.h"

class ePark : public eBuilding {
public:
    ePark(eGameBoard& board);

    std::shared_ptr<eTexture> getTexture(const eTileSize size) const;
private:
    const std::vector<eBuildingTextures>& mTextures;
};

#endif // EPARK_H
