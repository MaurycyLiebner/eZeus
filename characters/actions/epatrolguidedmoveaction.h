#ifndef EPATROLGUIDEDMOVEACTION_H
#define EPATROLGUIDEDMOVEACTION_H

#include "ecomplexaction.h"

struct ePatrolGuide {
    int fX;
    int fY;
};

class ePatrolGuidedMoveAction : public eComplexAction {
public:
    ePatrolGuidedMoveAction(eCharacter* const c,
                            const std::vector<ePatrolGuide>& guides,
                            const eAction& failAction,
                            const eAction& finishAction);

    void increment(const int by);
    void nextGuide();
private:
    const std::vector<ePatrolGuide> mGuides;
    int mNextGuide = 0;
    int mMaxDistance = 100;
    int mWalkedDistance = 0;
};

#endif // EPATROLGUIDEDMOVEACTION_H
