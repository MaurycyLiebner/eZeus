#include "efountain.h"

#include "characters/ewaterdistributor.h"

eFountain::eFountain() :
    ePatrolBuilding(&eBuildingTextures::fFountain,
                    -0.25, -1.5,
                    &eBuildingTextures::fFountainOverlay,
                    []() { return new eWaterDistributor; },
                    eBuildingType::fountain, 2, 2)  {

}
