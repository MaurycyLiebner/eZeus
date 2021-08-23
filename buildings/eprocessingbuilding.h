#ifndef EPROCESSINGBUILDING_H
#define EPROCESSINGBUILDING_H

#include "eresourcebuildingbase.h"

class eCartTransporter;

class eProcessingBuilding : public eResourceBuildingBase {
public:
    eProcessingBuilding(eGameBoard& board,
                        const eBuildingType type,
                        const int sw, const int sh,
                        const eResourceType rawMaterial,
                        const eResourceType product);

    void timeChanged();

    int count(const eResourceType type) const;
    int add(const eResourceType type, const int count);
    int spaceLeft(const eResourceType type) const;
private:
    bool spawnRawGetter();
    void depositRaw();
    void killCart();

    const eResourceType mRawMaterial;

    const int mMaxRaw = 8;

    eCartTransporter* mRawCart = nullptr;

    int mRawCount{0};

    int mProcessWaitTime = 5000;
    int mProcessTime = mProcessWaitTime;

    int mSpawnWaitTime = 5000;
    int mSpawnTime = mSpawnWaitTime;
    bool mSpawned{false};
};

#endif // EPROCESSINGBUILDING_H
