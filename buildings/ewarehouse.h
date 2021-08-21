#ifndef EWAREHOUSE_H
#define EWAREHOUSE_H

#include "estoragebuilding.h"

#include "textures/ebuildingtextures.h"

class eWarehouse : public eStorageBuilding {
public:
    eWarehouse(eGameBoard& board);

    eTexture getTexture(const eTileSize size) const;
    std::vector<eOverlay> getOverlays(const eTileSize size) const;
private:
    const std::vector<eBuildingTextures>& mTextures;
};

#endif // EWAREHOUSE_H
