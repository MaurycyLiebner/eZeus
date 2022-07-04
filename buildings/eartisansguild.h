#ifndef EARTISANSGUILD_H
#define EARTISANSGUILD_H

#include "eemployingbuilding.h"
#include "characters/eartisan.h"

class eArtisansGuild : public eEmployingBuilding {
public:
    eArtisansGuild(eGameBoard& board);
    ~eArtisansGuild();

    std::shared_ptr<eTexture> getTexture(const eTileSize size) const;
    std::vector<eOverlay> getOverlays(const eTileSize size) const;

    void timeChanged(const int by);

    using eArtisanPtr = stdsptr<eArtisan> eArtisansGuild::*;
    bool spawnArtisan(const eArtisanPtr artisan);
private:
    stdsptr<eArtisan> mArtisan;

    int mWaitTime = 2000;
    int mSpawnTime = mWaitTime;
};

#endif // EARTISANSGUILD_H
