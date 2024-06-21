#include "etheater.h"

#include "characters/eactor.h"
#include "textures/egametextures.h"

eTheater::eTheater(eGameBoard& board) :
    ePatrolTarget(board,
                  &eBuildingTextures::fTheater,
                  -1.25, -6.5,
                  &eBuildingTextures::fTheaterOverlay,
                  [this]() { return e::make_shared<eActor>(getBoard()); },
                  eBuildingType::theater, 5, 5, 18) {
    eGameTextures::loadTheater();
}
