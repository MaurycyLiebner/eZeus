#include "eshepherd.h"

eShepherd::eShepherd(eGameBoard& board) :
    eResourceCollector(board, &eCharacterTextures::fShepherd,
                       eCharacterType::shepherd) {}
