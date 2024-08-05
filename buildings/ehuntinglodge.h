#ifndef EHUNTINGLODGE_H
#define EHUNTINGLODGE_H

#include "eresourcecollectbuildingbase.h"

#include "textures/ebuildingtextures.h"

class eHunter;

class eHuntingLodge : public eResourceCollectBuildingBase {
public:
    eHuntingLodge(eGameBoard& board);
    ~eHuntingLodge();

    std::shared_ptr<eTexture> getTexture(const eTileSize size) const override;
    std::vector<eOverlay> getOverlays(const eTileSize size) const override;

    void timeChanged(const int by) override;

    void read(eReadStream& src) override;
    void write(eWriteStream& dst) const override;

    void addRaw() override {}
private:
    bool spawn();

    stdptr<eHunter> mHunter;
    int mSpawnTime = 1000000;
};

#endif // EHUNTINGLODGE_H
