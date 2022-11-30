#include "ebronzeminer.h"

#include "textures/egametextures.h"

eBronzeMiner::eBronzeMiner(eGameBoard& board) :
    eResourceCollector(board, &eCharacterTextures::fBronzeMiner,
                       eCharacterType::bronzeMiner) {
    eGameTextures::loadBronzeMiner();
}
