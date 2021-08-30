#ifndef ECOLLEGE_H
#define ECOLLEGE_H

#include "eemployingbuilding.h"
#include "textures/ebuildingtextures.h"
#include "characters/actions/epatrolaction.h"

class eCollege : public eEmployingBuilding {
public:
    eCollege(eGameBoard& board);

    std::shared_ptr<eTexture> getTexture(const eTileSize size) const;
    std::vector<eOverlay> getOverlays(const eTileSize size) const;
private:
    const std::vector<eBuildingTextures>& mTextures;
};

#endif // ECOLLEGE_H
