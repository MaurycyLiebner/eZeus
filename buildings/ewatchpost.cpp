#include "ewatchpost.h"

#include "characters/ewatchman.h"

eWatchpost::eWatchpost() :
    ePatrolBuilding(&eBuildingTextures::fWatchPost,
                    -0.25, -2.1,
                    &eBuildingTextures::fWatchPostOverlay,
                    []() { return new eWatchman; },
                    eBuildingType::watchPost, 2, 2)  {

}
