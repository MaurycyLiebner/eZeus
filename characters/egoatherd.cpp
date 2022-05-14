#include "egoatherd.h"

eGoatherd::eGoatherd(eGameBoard& board) :
    eShepherdBase(board, &eCharacterTextures::fGoatherd,
                  eCharacterType::goatherd) {}
