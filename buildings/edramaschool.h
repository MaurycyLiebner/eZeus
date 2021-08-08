#ifndef EDRAMASCHOOL_H
#define EDRAMASCHOOL_H

#include "ebuilding.h"
#include "textures/ebuildingtextures.h"
#include "characters/actions/epatrolaction.h"

class eDramaSchool : public eBuilding {
public:
    eDramaSchool(eGameBoard& board);

    eTexture getTexture(const eTileSize size) const;
    std::vector<eOverlay> getOverlays(const eTileSize size) const;
private:
    const std::vector<eBuildingTextures>& mTextures;
};


#endif // EDRAMASCHOOL_H
