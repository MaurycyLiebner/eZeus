#ifndef ERESOURCECOLLECTBUILDING_H
#define ERESOURCECOLLECTBUILDING_H

#include "ebuilding.h"

#include "textures/ebuildingtextures.h"

class eResourceCollector;

class eResourceCollectBuilding : public eBuilding {
public:
    using eHasResource = std::function<bool(eTile*)>;
    using eTranformFunc = std::function<void(eTile*)>;
    using eBaseTex = eTexture eBuildingTextures::*;
    using eOverlays = eTextureCollection eBuildingTextures::*;
    using eCharGenerator =  std::function<eResourceCollector*()>;
    eResourceCollectBuilding(eGameBoard& board,
                             const eBaseTex baseTex,
                             const double overlayX,
                             const double overlayY,
                             const eOverlays overlays,
                             const eCharGenerator& charGen,
                             const eBuildingType type,
                             const eHasResource& hr,
                             const eTranformFunc& tf,
                             const int sw, const int sh);

    eTexture getTexture(const eTileSize size) const;
    std::vector<eOverlay> getOverlays(const eTileSize size) const;

    void timeChanged();

    bool spawn();
private:
    const eCharGenerator mCharGenerator;
    const std::vector<eBuildingTextures>& mTextures;

    const eBaseTex mBaseTex;
    const eOverlays mOverlays;

    const double mOverlayX;
    const double mOverlayY;

    const eHasResource mHasRes;
    const eTranformFunc mTransFunc;

    int mWaitTime = 5000;
    int mSpawnTime = mWaitTime;

    int mResource{0};
};

#endif // ERESOURCECOLLECTBUILDING_H
