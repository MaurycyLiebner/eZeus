#include "emarbleminer.h"

eMarbleMiner::eMarbleMiner(eGameBoard& board) :
    eResourceCollector(board, &eCharacterTextures::fMarbleMiner,
                       eCharacterType::marbleMiner) {}
