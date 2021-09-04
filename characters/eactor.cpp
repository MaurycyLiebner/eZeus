#include "eactor.h"

eActor::eActor(eGameBoard& board) :
    eBasicPatroler(board, &eCharacterTextures::fActor,
                   eCharacterType::actor) {}
