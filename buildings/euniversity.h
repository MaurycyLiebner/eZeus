#ifndef EUNIVERSITY_H
#define EUNIVERSITY_H

#include "eemployingbuilding.h"

class eUniversity : public eEmployingBuilding {
public:
    eUniversity(eGameBoard& board);

    std::shared_ptr<eTexture> getTexture(const eTileSize size) const;
    std::vector<eOverlay> getOverlays(const eTileSize size) const;
};

#endif // EUNIVERSITY_H
