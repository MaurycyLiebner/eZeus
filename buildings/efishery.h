#ifndef EFISHERY_H
#define EFISHERY_H

#include "eresourcebuildingbase.h"

class eFishery : public eResourceBuildingBase {
public:
    eFishery(eGameBoard& board, const eOrientation o);

    std::shared_ptr<eTexture> getTexture(const eTileSize size) const;
    std::vector<eOverlay> getOverlays(const eTileSize size) const;
private:
    const eOrientation mO;

    bool mBuildingBoat = true;
};

#endif // EFISHERY_H
