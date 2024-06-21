#ifndef EDAIRY_H
#define EDAIRY_H

#include "eshepherbuildingbase.h"

class eGoatherd;

class eDairy : public eShepherBuildingBase {
public:
    eDairy(eGameBoard& board);

    std::vector<eOverlay> getOverlays(const eTileSize size) const;
private:
    const std::vector<eBuildingTextures>& mTextures;
};

#endif // EDAIRY_H
