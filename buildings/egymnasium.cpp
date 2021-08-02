#include "egymnasium.h"

#include "characters/egymnast.h"
#include "textures/egametextures.h"

eGymnasium::eGymnasium() :
    ePatrolBuilding(&eBuildingTextures::fGymnasium,
                    0.3, -1.7,
                    &eBuildingTextures::fGymnasiumOverlay,
                    []() { return new eGymnast; },
                    eBuildingType::gymnasium, 3, 3) {

}
