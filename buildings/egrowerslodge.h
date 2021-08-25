#ifndef EGROWERSLODGE_H
#define EGROWERSLODGE_H

#include "ebuildingwithresource.h"

#include "textures/ebuildingtextures.h"
#include "characters/egrower.h"

class eCartTransporter;

class eGrowersLodge : public eBuildingWithResource {
public:
    eGrowersLodge(eGameBoard& board);

    eTexture getTexture(const eTileSize size) const;
    std::vector<eOverlay> getOverlays(const eTileSize size) const;

    void timeChanged();

    int add(const eResourceType type, const int count);
    int take(const eResourceType type, const int count);

    int count(const eResourceType type) const;
    int spaceLeft(const eResourceType type) const;

    bool spawnCart(const eResourceType resType);
    bool spawnGrower(stdsptr<eGrower> eGrowersLodge::*grower);
private:
    const std::vector<eBuildingTextures>& mTextures;

    const int mMaxResource = 8;

    int mGrapes{0};
    int mOlives{0};

    stdsptr<eCartTransporter> mCart;
    const int mCartWaitTime = 5000;
    int mCartSpawnTime = mCartWaitTime;

    stdsptr<eGrower> mGrower1;
    stdsptr<eGrower> mGrower2;
    const int mGrowerWaitTime = 5000;
    int mGrowerSpawnTime = mGrowerWaitTime;
};

#endif // EGROWERSLODGE_H
