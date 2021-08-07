#include "epodium.h"

#include "characters/ephilosopher.h"
#include "textures/egametextures.h"

ePodium::ePodium() :
    ePatrolBuilding(&eBuildingTextures::fPodium,
                    -2.25, -3.78,
                    &eBuildingTextures::fPodiumOverlay,
                    []() { return new ePhilosopher; },
                    eBuildingType::podium, 2, 2) {
}
