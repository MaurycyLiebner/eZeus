#ifndef EPATROLGUIDEDMOVEACTION_H
#define EPATROLGUIDEDMOVEACTION_H

#include "ecomplexaction.h"

#include <SDL2/SDL_rect.h>

struct ePatrolGuide {
    int fX;
    int fY;
};

class ePatrolGuidedMoveAction : public eComplexAction {
public:
    ePatrolGuidedMoveAction(eCharacter* const c,
                            const SDL_Rect& buildingRect,
                            const std::vector<ePatrolGuide>& guides,
                            const eAction& failAction,
                            const eAction& finishAction);

    void increment(const int by);
    void nextGuide();
private:
    const std::vector<ePatrolGuide> mGuides;
    const SDL_Rect mBuildingRect;
    int mNextGuide = 0;
    int mMaxDistance = 100;
    int mWalkedDistance = 0;
};

#endif // EPATROLGUIDEDMOVEACTION_H
