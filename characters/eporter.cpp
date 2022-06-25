#include "eporter.h"

ePorter::ePorter(eGameBoard& board) :
    eBasicPatroler(board, &eCharacterTextures::fPorter,
                   eCharacterType::porter) {}
