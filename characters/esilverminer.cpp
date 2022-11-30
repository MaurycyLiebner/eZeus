#include "esilverminer.h"

#include "textures/egametextures.h"

eSilverMiner::eSilverMiner(eGameBoard& board) :
    eResourceCollector(board, &eCharacterTextures::fSilverMiner,
                       eCharacterType::silverMiner) {
    eGameTextures::loadSilverMiner();
}
