#include "efountain.h"

#include "characters/ewaterdistributor.h"

eFountain::eFountain() :
    ePatrolBuilding(&eBuildingTextures::fFountain,
                    -1.15, -2.37,
                    &eBuildingTextures::fFountainOverlay,
                    []() { return new eWaterDistributor; },
                    eBuildingType::fountain, 2, 2)  {

}
