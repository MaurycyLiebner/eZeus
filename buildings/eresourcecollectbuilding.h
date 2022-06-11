#ifndef ERESOURCECOLLECTBUILDING_H
#define ERESOURCECOLLECTBUILDING_H

#include "eresourcebuildingbase.h"

#include "textures/ebuildingtextures.h"

class eResourceCollectorBase;

class eResourceCollectBuilding : public eResourceBuildingBase {
public:
    using eHasResource = std::function<bool(eTileBase*)>;
    using eTranformFunc = std::function<void(eTile*)>;
    using eBaseTex = std::shared_ptr<eTexture> eBuildingTextures::*;
    using eOverlays = eTextureCollection eBuildingTextures::*;
    using eCharGenerator =  std::function<stdsptr<eResourceCollectorBase>()>;
    eResourceCollectBuilding(eGameBoard& board,
                             const eBaseTex baseTex,
                             const double overlayX,
                             const double overlayY,
                             const eOverlays overlays,
                             const int waitingOO,
                             const double waitingOX,
                             const double waitingOY,
                             const eCharGenerator& charGen,
                             const eBuildingType type,
                             const eHasResource& hr,
                             const eTranformFunc& tf,
                             const int sw, const int sh,
                             const int maxEmployees,
                             const eResourceType resType);
    ~eResourceCollectBuilding();

    std::shared_ptr<eTexture> getTexture(const eTileSize size) const;
    std::vector<eOverlay> getOverlays(const eTileSize size) const;

    void timeChanged(const int by);

    bool spawn();

    void setAddResource(const bool b) { mAddResource = b; }

    void addRaw();
protected:
    void enableSpawn() { mSpawnEnabled = true; }
    void disableSpawn() { mSpawnEnabled = false; }

    using eTileAction = std::function<void(eTile*)>;
    void setCollectedAction(const eTileAction& a);

    int rawCount() const { return mRawCount; }
    void setRawInc(const int i) { mRawInc = i; }

    void setRawCountCollect(const int r) { mRawCountCollect = r; }
private:
    const eCharGenerator mCharGenerator;
    const std::vector<eBuildingTextures>& mTextures;

    const eBaseTex mBaseTex;
    const eOverlays mOverlays;

    const double mOverlayX;
    const double mOverlayY;

    const int mWaitingOO = 0;
    const double mWaitingOX = 0;
    const double mWaitingOY = 0;

    const eHasResource mHasRes;
    const eTranformFunc mTransFunc;

    eTileAction mCollectedAction;

    stdsptr<eResourceCollectorBase> mCollector;

    bool mSpawnEnabled = true;

    bool mAddResource = true;

    int mRawCount = 0;
    int mRawCountCollect = 0;
    int mRawInc = 1;
    int mProcessDuration = 10000;
    int mProcessTime = 0;

    int mWaitTime = 1500;
    int mSpawnTime = mWaitTime;
};

#endif // ERESOURCECOLLECTBUILDING_H
