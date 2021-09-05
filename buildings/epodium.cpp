#include "epodium.h"

#include "characters/ephilosopher.h"

ePodium::ePodium(eGameBoard& board) :
    ePatrolTarget(board,
                  eBuildingType::college,
                  &eBuildingTextures::fPodium,
                  -2.25, -3.78,
                  &eBuildingTextures::fPodiumOverlay,
                  [this]() { return e::make_shared<ePhilosopher>(getBoard()); },
                  eBuildingType::podium, 2, 2, 4) {
}
