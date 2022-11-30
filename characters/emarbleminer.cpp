#include "emarbleminer.h"

#include "textures/egametextures.h"

eMarbleMiner::eMarbleMiner(eGameBoard& board) :
    eResourceCollector(board, &eCharacterTextures::fMarbleMiner,
                       eCharacterType::marbleMiner) {
    eGameTextures::loadMarbleMiner();
}
