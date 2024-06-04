#ifndef EINVENTORSWORKSHOP_H
#define EINVENTORSWORKSHOP_H

#include "eemployingbuilding.h"
#include "textures/ebuildingtextures.h"

class eInventorsWorkshop : public eEmployingBuilding {
public:
    eInventorsWorkshop(eGameBoard& board);

    std::shared_ptr<eTexture> getTexture(const eTileSize size) const;
    std::vector<eOverlay> getOverlays(const eTileSize size) const;
};

#endif // EINVENTORSWORKSHOP_H
