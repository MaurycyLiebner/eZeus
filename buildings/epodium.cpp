#include "epodium.h"

#include "characters/ephilosopher.h"
#include "textures/egametextures.h"

ePodium::ePodium() :
    ePatrolBuilding(&eBuildingTextures::fPodium,
                    0.3, -1.7,
                    &eBuildingTextures::fPodiumOverlay,
                    []() { return new ePhilosopher; },
                    eBuildingType::podium, 2, 2) {
}
