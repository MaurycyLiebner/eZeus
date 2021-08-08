#include "epodium.h"

#include "characters/ephilosopher.h"
#include "textures/egametextures.h"

ePodium::ePodium(eGameBoard& board) :
    ePatrolBuilding(board,
                    &eBuildingTextures::fPodium,
                    -2.25, -3.78,
                    &eBuildingTextures::fPodiumOverlay,
                    [this]() { return new ePhilosopher(getBoard()); },
                    eBuildingType::podium, 2, 2) {
}
