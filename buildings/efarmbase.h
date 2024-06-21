#ifndef EFARMBASE_H
#define EFARMBASE_H

#include "eresourcebuildingbase.h"

#include "textures/ebuildingtextures.h"

class eFarmBase : public eResourceBuildingBase {
public:
    eFarmBase(eGameBoard& board,
              const eBuildingType type,
              const int sw, const int sh,
              const eResourceType resType);

    std::shared_ptr<eTexture> getTexture(const eTileSize size) const override;
    std::vector<eOverlay> getOverlays(const eTileSize size) const override;

    void timeChanged(const int by) override;

    void read(eReadStream& src) override;
    void write(eWriteStream& dst) const override;
private:
    const std::vector<eBuildingTextures>& mTextures;
    const int mWaitTime = 15000;
    int mNextRipe = 0;
    int mRipe = 0; // 0 - 5
};

#endif // EFARMBASE_H
