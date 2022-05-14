#include "eshepherd.h"

eShepherd::eShepherd(eGameBoard& board) :
    eShepherdBase(board, &eCharacterTextures::fShepherd,
                  eCharacterType::shepherd) {}
