#include "eorichalcminer.h"

#include "textures/egametextures.h"

eOrichalcMiner::eOrichalcMiner(eGameBoard& board) :
    eResourceCollector(board, &eCharacterTextures::fOrichalcMiner,
                       eCharacterType::orichalcMiner) {
    eGameTextures::loadOrichalcMiner();
}
