#ifndef ECHARIOTFACTORY_H
#define ECHARIOTFACTORY_H

#include "eemployingbuilding.h"

class eChariotFactory : public eEmployingBuilding {
public:
    eChariotFactory(eGameBoard& board);
    ~eChariotFactory();

    std::shared_ptr<eTexture> getTexture(const eTileSize size) const override;
    std::vector<eOverlay> getOverlays(const eTileSize size) const override;

    void timeChanged(const int by) override;

    int add(const eResourceType type, const int count) override;
    int take(const eResourceType type, const int count) override;

    int count(const eResourceType type) const override;
    int spaceLeft(const eResourceType type) const override;

    std::vector<eCartTask> cartTasks() const override;

    void read(eReadStream& src) override;
    void write(eWriteStream& dst) const override;

    int wood() const { return mWood; }
    int horses() const { return mHorses; }
    int chariotCount() const { return std::min(mHorses, mChariots); }
private:
    int mWood = 0;
    int mChariotBuildingTime = 0;
    int mHorses = 0;
    int mChariots = 0;

    stdptr<eCartTransporter> mWheatCart;
    stdptr<eCartTransporter> mHorseCart;
};

#endif // ECHARIOTFACTORY_H
