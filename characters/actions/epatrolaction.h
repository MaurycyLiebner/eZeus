#ifndef EPATROLACTION_H
#define EPATROLACTION_H

#include "eactionwithcomeback.h"
#include "engine/emovedirection.h"
#include "epatrolmoveaction.h"
#include "epatrolguidedmoveaction.h"
#include "buildings/ebuilding.h"

class ePatrolBuilding;

class ePatrolAction : public eActionWithComeback {
public:
    ePatrolAction(eCharacter* const c,
                  ePatrolBuilding* const b,
                  const std::vector<ePatrolGuide>& guides,
                  const eAction& failAction,
                  const eAction& finishAction);

    bool decide();
protected:
    void patrol();
    void goBackDecision();
    void goBackNoRoad();
private:
    const std::vector<ePatrolGuide> mGuides;
    ePatrolBuilding* const mBuilding;

    bool mDone = false;
    bool mWaited = true;
};

#endif // EPATROLACTION_H
