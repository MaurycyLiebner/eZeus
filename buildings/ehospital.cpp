#include "ehospital.h"

#include "characters/ehealer.h"

eHospital::eHospital() :
    ePatrolBuilding(&eBuildingTextures::fHospital,
                    -1.78, -4.5,
                    &eBuildingTextures::fHospitalOverlay,
                    []() { return new eHealer; },
                    eBuildingType::hospital, 4, 4)  {

}
