#include "ehealer.h"

eHealer::eHealer(eGameBoard& board) :
    eBasicPatroler(board, &eCharacterTextures::fHealer) {}
