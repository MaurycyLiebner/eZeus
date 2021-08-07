#include "egymnasium.h"

#include "characters/egymnast.h"
#include "textures/egametextures.h"

eGymnasium::eGymnasium() :
    ePatrolBuilding(&eBuildingTextures::fGymnasium,
                    -2.57, -4.57,
                    &eBuildingTextures::fGymnasiumOverlay,
                    []() { return new eGymnast; },
                    eBuildingType::gymnasium, 3, 3) {

}
