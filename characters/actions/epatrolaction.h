#ifndef EPATROLACTION_H
#define EPATROLACTION_H

#include "eactionwithcomeback.h"
#include "engine/emovedirection.h"
#include "epatrolmoveaction.h"
#include "epatrolguidedmoveaction.h"

class ePatrolAction : public eActionWithComeback {
public:
    ePatrolAction(eCharacter* const c,
                  const std::vector<ePatrolGuide>& guides,
                  const eAction& failAction,
                  const eAction& finishAction);

    void increment(const int by);
protected:
    void patrol();
    void goBack2();
    void goBackNoRoad();
private:
    const std::vector<ePatrolGuide> mGuides;
};

#endif // EPATROLACTION_H
