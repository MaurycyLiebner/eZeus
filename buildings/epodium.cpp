#include "epodium.h"

#include "characters/ephilosopher.h"
#include "textures/egametextures.h"

ePodium::ePodium() :
    ePatrolBuilding(&eBuildingTextures::fPodium,
                    0.45, -1.05,
                    &eBuildingTextures::fPodiumOverlay,
                    []() { return new ePhilosopher; },
                    eBuildingType::podium, 2, 2) {
}
