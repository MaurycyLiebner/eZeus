#ifndef EPROCESSINGBUILDING_H
#define EPROCESSINGBUILDING_H

#include "eresourcebuildingbase.h"
#include "textures/ebuildingtextures.h"

class eCartTransporter;

class eProcessingBuilding : public eResourceBuildingBase {
public:
    using eBaseTex = eTexture eBuildingTextures::*;
    using eOverlays = eTextureCollection eBuildingTextures::*;
    eProcessingBuilding(eGameBoard& board,
                        const eBaseTex baseTex,
                        const double overlayX,
                        const double overlayY,
                        const eOverlays overlays,
                        const eBuildingType type,
                        const int sw, const int sh,
                        const int maxEmployees,
                        const eResourceType rawMaterial,
                        const eResourceType product,
                        const int rawUse,
                        const int time);

    eTexture getTexture(const eTileSize size) const;
    std::vector<eOverlay> getOverlays(const eTileSize size) const;

    void timeChanged();

    int count(const eResourceType type) const;
    int add(const eResourceType type, const int count);
    int spaceLeft(const eResourceType type) const;
private:
    bool spawnRawGetter();
    void depositRaw();
    void killCart();

    const std::vector<eBuildingTextures>& mTextures;

    const eBaseTex mBaseTex;
    const eOverlays mOverlays;
    const double mOverlayX;
    const double mOverlayY;

    const eResourceType mRawMaterial;

    const int mMaxRaw = 4;
    const int mRawUse;

    stdsptr<eCartTransporter> mRawCart;

    int mRawCount{0};

    int mProcessWaitTime;
    int mProcessTime = mProcessWaitTime;

    int mSpawnWaitTime = 5000;
    int mSpawnTime = mSpawnWaitTime;
};

#endif // EPROCESSINGBUILDING_H
