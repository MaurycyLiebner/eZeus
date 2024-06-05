#include "ecurator.h"

#include "textures/egametextures.h"

eCurator::eCurator(eGameBoard& board) :
    eBasicPatroler(board, &eCharacterTextures::fCurator,
                   eCharacterType::curator) {
    eGameTextures::loadCurator();
    setProvide(eProvide::competitorCurator, 10000);
}
