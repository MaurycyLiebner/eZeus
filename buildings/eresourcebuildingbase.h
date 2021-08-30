#ifndef ERESOURCEBUILDINGBASE_H
#define ERESOURCEBUILDINGBASE_H

#include "eemployingbuilding.h"

class eCartTransporter;

class eResourceBuildingBase : public eEmployingBuilding {
public:
    eResourceBuildingBase(eGameBoard& board,
                          const eBuildingType type,
                          const int sw, const int sh,
                          const int maxEmployees,
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
    bool spawnCart();

    const int mMaxResource = 8;

    const eResourceType mResType;

    int mResource{0};

    stdsptr<eCartTransporter> mCart;
    int mCartWaitTime = 5000;
    int mCartSpawnTime = mCartWaitTime;
};

#endif // ERESOURCEBUILDINGBASE_H
