#ifndef ECARDINGSHED_H
#define ECARDINGSHED_H

#include "eshepherbuildingbase.h"

class eShepherd;

class eCardingShed : public eShepherBuildingBase {
public:
    eCardingShed(eGameBoard& board);

    std::vector<eOverlay> getOverlays(const eTileSize size) const;
private:
    const std::vector<eBuildingTextures>& mTextures;
};

#endif // ECARDINGSHED_H
