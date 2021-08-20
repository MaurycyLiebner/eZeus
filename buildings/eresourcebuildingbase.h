#ifndef ERESOURCEBUILDINGBASE_H
#define ERESOURCEBUILDINGBASE_H

#include "ebuilding.h"

#include "engine/eresourcetype.h"

class eResourceBuildingBase : public eBuilding {
public:
    eResourceBuildingBase(eGameBoard& board,
                          const eBuildingType type,
                          const int sw, const int sh,
                          const eResourceType resType);

    int resource() const { return mResource; }
    int incResource(const int by);

    int maxResource() const { return mMaxResource; }

    void timeChanged();

    bool spawn();
private:
    const int mMaxResource = 8;

    const eResourceType mResType;

    int mResource{0};

    int mWaitTime = 5000;
    int mSpawnTime = mWaitTime;
    bool mSpawned{false};
};

#endif // ERESOURCEBUILDINGBASE_H
