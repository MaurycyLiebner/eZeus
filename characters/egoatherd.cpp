#include "egoatherd.h"

eGoatherd::eGoatherd(eGameBoard& board) :
    eResourceCollector(board, &eCharacterTextures::fGoatherd,
                       eCharacterType::goatherd) {}
