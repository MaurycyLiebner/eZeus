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
                        const eResourceType rawMaterial,
                        const eResourceType product);

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

    const int mMaxRaw = 8;

    eCartTransporter* mRawCart = nullptr;

    int mRawCount{0};

    int mProcessWaitTime = 5000;
    int mProcessTime = mProcessWaitTime;

    int mSpawnWaitTime = 5000;
    int mSpawnTime = mSpawnWaitTime;
    bool mSpawned{false};
};

#endif // EPROCESSINGBUILDING_H
