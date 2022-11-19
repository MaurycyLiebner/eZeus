#ifndef EHUNTINGLODGE_H
#define EHUNTINGLODGE_H

#include "eresourcebuildingbase.h"

#include "textures/ebuildingtextures.h"

class eHunter;

class eHuntingLodge : public eResourceBuildingBase {
public:
    eHuntingLodge(eGameBoard& board);
    ~eHuntingLodge();

    std::shared_ptr<eTexture> getTexture(const eTileSize size) const override;
    std::vector<eOverlay> getOverlays(const eTileSize size) const override;

    void timeChanged(const int by) override;

    void read(eReadStream& src) override;
    void write(eWriteStream& dst) const override;
private:
    bool spawn();

    stdptr<eHunter> mHunter;
    const int mWaitTime = 5000;
    int mSpawnTime = mWaitTime;
};

#endif // EHUNTINGLODGE_H
