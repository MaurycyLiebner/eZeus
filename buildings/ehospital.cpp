#include "ehospital.h"

#include "characters/ehealer.h"

eHospital::eHospital() :
    ePatrolBuilding(&eBuildingTextures::fHospital,
                    0.33, -2.4,
                    &eBuildingTextures::fHospitalOverlay,
                    []() { return new eHealer; },
                    eBuildingType::hospital, 4, 4)  {

}
