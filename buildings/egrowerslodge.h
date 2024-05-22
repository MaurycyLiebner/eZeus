#ifndef EGROWERSLODGE_H
#define EGROWERSLODGE_H

#include "eemployingbuilding.h"

#include "textures/ebuildingtextures.h"
#include "characters/egrower.h"

class eCartTransporter;

class eGrowersLodge : public eEmployingBuilding {
public:
    eGrowersLodge(eGameBoard& board, const eGrowerType type);
    ~eGrowersLodge();

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

    using eGrowerPtr = stdptr<eGrower> eGrowersLodge::*;
    bool spawnGrower(const eGrowerPtr grower);

    void setNoTarget(const bool t);
    bool noTarget() const { return mNoTarget; }
private:
    const int mMaxResource = 8;

    const eGrowerType mType;

    bool mNoTarget = false;

    bool mSpawnEnabled = true;

    int mGrapes{0};
    int mOlives{0};
    int mOranges{0};

    stdptr<eCartTransporter> mCart;

    int mWaitTime = 5000;
    int mSpawnTime = mWaitTime;

    stdptr<eGrower> mGrower;
};

#endif // EGROWERSLODGE_H
