#include "egoatherd.h"

#include "textures/egametextures.h"

eGoatherd::eGoatherd(eGameBoard& board) :
    eShepherdBase(board, &eCharacterTextures::fGoatherd,
                  eCharacterType::goatherd) {
    eGameTextures::loadGoatherd();
}
