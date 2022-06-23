#ifndef EFISHERY_H
#define EFISHERY_H

#include "eresourcecollectbuildingbase.h"

class eFishingBoat;

class eCollectResourceAction;

enum class eFisheryState {
    buildingBoat,
    waiting,
    unpacking
};

class eFishery : public eResourceCollectBuildingBase {
public:
    eFishery(eGameBoard& board, const eOrientation o);
    ~eFishery();

    void timeChanged(const int by);

    std::shared_ptr<eTexture> getTexture(const eTileSize size) const;
    std::vector<eOverlay> getOverlays(const eTileSize size) const;

    void addRaw();

    int take(const eResourceType type, const int count);
private:
    void spawnBoat();
    void updateDisabled();

    bool mDisabled = false;
    const eOrientation mO;
    stdsptr<eFishingBoat> mBoat;
    stdptr<eCollectResourceAction> mAction;
    int mStateCount = 0;
    eFisheryState mState = eFisheryState::buildingBoat;

};

#endif // EFISHERY_H
