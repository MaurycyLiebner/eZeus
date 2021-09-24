#ifndef ETOWER_H
#define ETOWER_H

#include "eemployingbuilding.h"

class eTower : public eEmployingBuilding {
public:
    eTower(eGameBoard& board);

    std::shared_ptr<eTexture>
    getTexture(const eTileSize size) const;
    std::vector<eOverlay>
    getOverlays(const eTileSize size) const;
};

#endif // ETOWER_H
