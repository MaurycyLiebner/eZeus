#ifndef EDRAMASCHOOL_H
#define EDRAMASCHOOL_H

#include "eemployingbuilding.h"
#include "textures/ebuildingtextures.h"
#include "characters/actions/epatrolaction.h"

class eDramaSchool : public eEmployingBuilding {
public:
    eDramaSchool(eGameBoard& board);

    std::shared_ptr<eTexture> getTexture(const eTileSize size) const;
    std::vector<eOverlay> getOverlays(const eTileSize size) const;
private:
    const std::vector<eBuildingTextures>& mTextures;
};


#endif // EDRAMASCHOOL_H
