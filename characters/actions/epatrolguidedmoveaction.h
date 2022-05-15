#ifndef EPATROLGUIDEDMOVEACTION_H
#define EPATROLGUIDEDMOVEACTION_H

#include "eactionwithcomeback.h"

#include <SDL2/SDL_rect.h>

struct ePatrolGuide {
    int fX;
    int fY;
};

class ePatrolGuidedMoveAction : public eActionWithComeback {
public:
    ePatrolGuidedMoveAction(eCharacter* const c,
                            eBuilding* const b,
                            const std::vector<ePatrolGuide>& guides,
                            const eAction& failAction,
                            const eAction& finishAction);

    bool decide();
    void nextGuide();
private:
    const std::vector<ePatrolGuide> mGuides;
    eBuilding* const mBuilding;
    int mNextGuide = 0;
    int mMaxDistance = 100;
    int mWalkedDistance = 0;

    bool mGuideFail = false;
};

#endif // EPATROLGUIDEDMOVEACTION_H
