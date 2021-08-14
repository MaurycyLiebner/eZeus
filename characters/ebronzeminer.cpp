#include "ebronzeminer.h"

eBronzeMiner::eBronzeMiner(eGameBoard& board) :
    eResourceCollector(board, &eCharacterTextures::fBronzeMiner,
                       eCharacterType::bronzeMiner) {}
