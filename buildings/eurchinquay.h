#ifndef EURCHINQUAY_H
#define EURCHINQUAY_H

#include "eresourcecollectbuildingbase.h"

class eUrchinGatherer;

enum class eUrchinQuayState {
    waiting,
    unpacking
};

class eUrchinQuay : public eResourceCollectBuildingBase {
public:
    eUrchinQuay(eGameBoard& board, const eOrientation o);
    ~eUrchinQuay();

    void timeChanged(const int by) override;

    std::shared_ptr<eTexture> getTexture(const eTileSize size) const override;
    std::vector<eOverlay> getOverlays(const eTileSize size) const override;

    void addRaw() override;

    int take(const eResourceType type, const int count) override;

    void read(eReadStream& src) override;
    void write(eWriteStream& dst) const override;

    eOrientation orientation() const { return mO; }

    eUrchinQuayState state() const { return mState; }
private:
    void spawnGatherer();
    void updateDisabled();

    const eOrientation mO;

    bool mDisabled = false;
    int mStateCount = 0;
    eUrchinQuayState mState = eUrchinQuayState::waiting;
    stdptr<eUrchinGatherer> mGatherer;
};

#endif // EURCHINQUAY_H
