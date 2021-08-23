#ifndef ERESOURCEBUILDINGBASE_H
#define ERESOURCEBUILDINGBASE_H

#include "ebuildingwithresource.h"

class eResourceBuildingBase : public eBuildingWithResource {
public:
    eResourceBuildingBase(eGameBoard& board,
                          const eBuildingType type,
                          const int sw, const int sh,
                          const eResourceType resType);

    int add(const eResourceType type, const int count);
    int take(const eResourceType type, const int count);

    int count(const eResourceType type) const;
    int spaceLeft(const eResourceType type) const;

    eResourceType resourceType() const { return mResType; }
    int resource() const { return mResource; }
    int maxResource() const { return mMaxResource; }

    void timeChanged();
private:
    bool spawn();

    const int mMaxResource = 8;

    const eResourceType mResType;

    int mResource{0};

    int mWaitTime = 5000;
    int mSpawnTime = mWaitTime;
    bool mSpawned{false};
};

#endif // ERESOURCEBUILDINGBASE_H
