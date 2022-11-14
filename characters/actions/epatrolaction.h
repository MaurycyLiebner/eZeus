#ifndef EPATROLACTION_H
#define EPATROLACTION_H

#include "eactionwithcomeback.h"
#include "engine/emovedirection.h"
#include "epatrolmoveaction.h"
#include "epatrolguidedmoveaction.h"
#include "buildings/ebuilding.h"
#include "emovetoaction.h"

class ePatrolBuildingBase;

class ePatrolAction : public eActionWithComeback {
public:
    ePatrolAction(eCharacter* const c,
                  ePatrolBuildingBase* const b,
                  const std::vector<ePatrolGuide>& guides,
                  const stdsptr<eDirectionTimes>& dirTimes = {});

    bool decide();
protected:
    void patrol();
    void goBackDecision(const stdsptr<eWalkableObject>& w =
                            eWalkableObject::sCreateRoad());
private:
    const std::vector<ePatrolGuide> mGuides;
    const stdsptr<eDirectionTimes> mDirTimes;
    ePatrolBuildingBase* const mBuilding;

    bool mDone = false;
};

#endif // EPATROLACTION_H
