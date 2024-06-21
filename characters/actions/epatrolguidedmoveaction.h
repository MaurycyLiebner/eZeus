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
                            const std::vector<ePatrolGuide>& guides);
    ePatrolGuidedMoveAction(eCharacter* const c);

    bool decide() override;

    void read(eReadStream& src) override;
    void write(eWriteStream& dst) const override;

    void nextGuide();

    void setMaxWalkDistance(const int dist)
    { mMaxWalkDistance = dist; }
private:
    std::vector<ePatrolGuide> mGuides;
    ePatrolBuildingBase* mBuilding = nullptr;
    int mNextGuide = 0;
    int mMaxWalkDistance = 100;
    int mWalkedDistance = 0;
};

#endif // EPATROLGUIDEDMOVEACTION_H
