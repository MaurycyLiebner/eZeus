#ifndef EHUNTINGLODGE_H
#define EHUNTINGLODGE_H

#include "eresourcebuildingbase.h"

#include "textures/ebuildingtextures.h"

class eHunter;

class eHuntingLodge : public eResourceBuildingBase {
public:
    eHuntingLodge(eGameBoard& board);

    eTexture getTexture(const eTileSize size) const;
    std::vector<eOverlay> getOverlays(const eTileSize size) const;

    void timeChanged();

    bool spawn();
private:
    const std::vector<eBuildingTextures>& mTextures;

    stdsptr<eHunter> mHunter;
    int mWaitTime = 5000;
    int mSpawnTime = mWaitTime;
};

#endif // EHUNTINGLODGE_H
