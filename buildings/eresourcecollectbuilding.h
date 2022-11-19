#ifndef ERESOURCECOLLECTBUILDING_H
#define ERESOURCECOLLECTBUILDING_H

#include "eresourcecollectbuildingbase.h"

#include "textures/ebuildingtextures.h"
#include "characters/actions/ecollectresourceaction.h"

class eResourceCollectorBase;

class eResourceCollectBuilding : public eResourceCollectBuildingBase {
public:
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
                             const stdsptr<eHasResourceObject>& hr,
                             const int sw, const int sh,
                             const int maxEmployees,
                             const eResourceType resType);
    ~eResourceCollectBuilding();

    std::shared_ptr<eTexture> getTexture(const eTileSize size) const override;
    std::vector<eOverlay> getOverlays(const eTileSize size) const override;

    void timeChanged(const int by) override;

    void addRaw() override;

    bool spawn();

    void setAddResource(const bool b) { mAddResource = b; }

    void read(eReadStream& src) override;
    void write(eWriteStream& dst) const override;
protected:
    void enableSpawn() { mSpawnEnabled = true; }
    void disableSpawn() { mSpawnEnabled = false; }

    void setCollectedAction(const eTileActionType a);

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

    const stdsptr<eHasResourceObject> mHasRes;

    eTileActionType mCollectedAction = eTileActionType::none;

    stdptr<eResourceCollectorBase> mCollector;

    bool mSpawnEnabled = true;

    bool mAddResource = true;

    int mRawCount = 0;
    int mRawCountCollect = 0;
    int mRawInc = 1;
    int mProcessDuration = 10000;
    int mProcessTime = 0;

    int mWaitTime = 5000;
    int mSpawnTime = mWaitTime;
};

#endif // ERESOURCECOLLECTBUILDING_H
