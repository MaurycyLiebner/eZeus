#ifndef EHUNTINGLODGE_H
#define EHUNTINGLODGE_H

#include "eresourcebuildingbase.h"

#include "textures/ebuildingtextures.h"

class eHuntingLodge : public eResourceBuildingBase {
public:
    eHuntingLodge(eGameBoard& board);

    eTexture getTexture(const eTileSize size) const;
    std::vector<eOverlay> getOverlays(const eTileSize size) const;

    void timeChanged();

    bool spawn();
private:
    const std::vector<eBuildingTextures>& mTextures;

    int mWaitTime = 5000;
    int mSpawnTime = mWaitTime;
    bool mSpawned{false};
};

#endif // EHUNTINGLODGE_H
