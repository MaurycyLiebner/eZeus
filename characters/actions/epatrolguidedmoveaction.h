#ifndef EPATROLGUIDEDMOVEACTION_H
#define EPATROLGUIDEDMOVEACTION_H

#include "ecomplexaction.h"

#include <SDL2/SDL_rect.h>

class ePatrolBuildingBase;

struct ePatrolGuide {
    int fX;
    int fY;
};

class ePatrolGuidedMoveAction : public eComplexAction {
public:
    ePatrolGuidedMoveAction(eCharacter* const c,
                            ePatrolBuildingBase* const b,
                            const std::vector<ePatrolGuide>& guides,
                            const eAction& failAction,
                            const eAction& finishAction);

    bool decide();
    void nextGuide();

    void setMaxWalkDistance(const int dist)
    { mMaxWalkDistance = dist; }
private:
    const std::vector<ePatrolGuide> mGuides;
    ePatrolBuildingBase* const mBuilding;
    int mNextGuide = 0;
    int mMaxWalkDistance = 100;
    int mWalkedDistance = 0;
};

#endif // EPATROLGUIDEDMOVEACTION_H
