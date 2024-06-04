#include "eobservatory.h"

#include "characters/eastronomer.h"
#include "textures/egametextures.h"

eObservatory::eObservatory(eGameBoard& board) :
    ePatrolTarget(board,
                  eBuildingType::university,
                  &eBuildingTextures::fObservatory,
                  -8.15, -10.65,
                  &eBuildingTextures::fObservatoryOverlay,
                  [this]() { return e::make_shared<eAstronomer>(getBoard()); },
                  eBuildingType::observatory, 5, 5, 18) {
    eGameTextures::loadObservatory();
}
