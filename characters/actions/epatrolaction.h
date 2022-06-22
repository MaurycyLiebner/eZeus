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
                  const eAction& failAction,
                  const eAction& finishAction);

    bool decide();
protected:
    void patrol();
    void goBackDecision(const eWalkable& w =
                            eWalkableHelpers::sRoadWalkable);
private:
    const std::vector<ePatrolGuide> mGuides;
    ePatrolBuildingBase* const mBuilding;

    bool mDone = false;
};

#endif // EPATROLACTION_H
