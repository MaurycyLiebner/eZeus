#include "eastronomer.h"

#include "textures/egametextures.h"

eAstronomer::eAstronomer(eGameBoard& board) :
    eBasicPatroler(board, &eCharacterTextures::fAstronomer,
                   eCharacterType::astronomer) {
    eGameTextures::loadAstronomer();
    setProvide(eProvide::actorAstronomer, 10000);
}
