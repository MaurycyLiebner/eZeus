#ifndef EPROCESSINGBUILDING_H
#define EPROCESSINGBUILDING_H

#include "eresourcebuildingbase.h"
#include "textures/ebuildingtextures.h"

class eCartTransporter;

class eProcessingBuilding : public eResourceBuildingBase {
public:
    using eBaseTex = std::shared_ptr<eTexture> eBuildingTextures::*;
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
    ~eProcessingBuilding();

    std::shared_ptr<eTexture> getTexture(const eTileSize size) const;
    std::vector<eOverlay> getOverlays(const eTileSize size) const;

    void timeChanged(const int by);

    int add(const eResourceType type, const int count);

    int count(const eResourceType type) const;
    int spaceLeft(const eResourceType type) const;

    std::vector<eCartTask> cartTasks() const;
private:
    const std::vector<eBuildingTextures>& mTextures;

    const eBaseTex mBaseTex;
    const eOverlays mOverlays;
    const double mOverlayX;
    const double mOverlayY;

    const eResourceType mRawMaterial;

    stdsptr<eCartTransporter> mTakeCart;

    const int mMaxRaw = 4;
    const int mRawUse;
    int mRawCount{0};

    int mProcessWaitTime;
    int mProcessTime = mProcessWaitTime;
};

#endif // EPROCESSINGBUILDING_H
