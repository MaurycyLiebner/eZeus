#ifndef EPATROLTARGET_H
#define EPATROLTARGET_H

#include "epatrolbuilding.h"

class ePatrolTarget : public ePatrolBuilding {
public:
    ePatrolTarget(eGameBoard& board,
                  const eBuildingType fromBuilding,
                  const eBaseTex baseTex,
                  const double overlayX,
                  const double overlayY,
                  const eOverlays overlays,
                  const eCharGenerator& charGen,
                  const eBuildingType type,
                  const int sw, const int sh,
                  const int maxEmployees);
private:
    void timeChanged(const int by);
    void spawnGetActor();

    const eBuildingType mFromBuilding;
    const eCharGenerator mCharGen;

    int mActor = -1;

    const int mWaitTime = 20000;
    int mSpawnTime = 0;
    stdsptr<eCharacter> mChar;
};

#endif // EPATROLTARGET_H
