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

    std::shared_ptr<eTexture> getTexture(const eTileSize size) const;
    std::vector<eOverlay> getOverlays(const eTileSize size) const;

    void timeChanged(const int by);

    int add(const eResourceType type, const int count);
    int take(const eResourceType type, const int count);

    int count(const eResourceType type) const;
    int spaceLeft(const eResourceType type) const;

    bool spawnCart(const eResourceType resType);
    using eGrowerPtr = stdsptr<eGrower> eGrowersLodge::*;
    bool spawnGrower(const eGrowerPtr grower);
private:
    const std::vector<eBuildingTextures>& mTextures;

    const int mMaxResource = 8;

    const eGrowerType mType;

    int mGrapes{0};
    int mOlives{0};
    int mOranges{0};

    stdsptr<eTransporterBase> mCart;
    const int mCartWaitTime = 5000;
    int mCartSpawnTime = mCartWaitTime;

    stdsptr<eGrower> mGrower1;
    stdsptr<eGrower> mGrower2;
};

#endif // EGROWERSLODGE_H
