#ifndef EHUNTINGLODGE_H
#define EHUNTINGLODGE_H

#include "ebuilding.h"

#include "textures/ebuildingtextures.h"

class eHuntingLodge : public eBuilding {
public:
    eHuntingLodge(eGameBoard& board);

    eTexture getTexture(const eTileSize size) const;
    std::vector<eOverlay> getOverlays(const eTileSize size) const;
private:
    const std::vector<eBuildingTextures>& mTextures;
};

#endif // EHUNTINGLODGE_H
