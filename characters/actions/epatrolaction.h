#ifndef EPATROLACTION_H
#define EPATROLACTION_H

#include "eactionwithcomeback.h"
#include "engine/emovedirection.h"
#include "epatrolmoveaction.h"

class ePatrolAction : public eActionWithComeback {
public:
    ePatrolAction(eCharacter* const c,
                  const std::vector<ePatrolGuide>& guides,
                  const eAction& failAction,
                  const eAction& finishAction);

    void increment(const int by);
protected:
    void patrol();
    bool goBack2();
    bool goBackNoRoad();
private:
    const std::vector<ePatrolGuide> mGuides;

    int mStartX = 0;
    int mStartY = 0;
};

#endif // EPATROLACTION_H
