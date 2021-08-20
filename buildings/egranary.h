#ifndef EGRANARY_H
#define EGRANARY_H

#include "estoragebuilding.h"

#include "textures/ebuildingtextures.h"

class eGranary : public eStorageBuilding {
public:
    eGranary(eGameBoard& board);

    eTexture getTexture(const eTileSize size) const;
    std::vector<eOverlay> getOverlays(const eTileSize size) const;
private:
    const std::vector<eBuildingTextures>& mTextures;
};

#endif // EGRANARY_H
