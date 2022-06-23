#ifndef EFISHERY_H
#define EFISHERY_H

#include "eresourcebuildingbase.h"

enum class eFisheryState {
    buildingBoat,
    waiting,
    unpacking
};

class eFishery : public eResourceBuildingBase {
public:
    eFishery(eGameBoard& board, const eOrientation o);

    std::shared_ptr<eTexture> getTexture(const eTileSize size) const;
    std::vector<eOverlay> getOverlays(const eTileSize size) const;
private:
    const eOrientation mO;

    eFisheryState mState = eFisheryState::buildingBoat;
};

#endif // EFISHERY_H
