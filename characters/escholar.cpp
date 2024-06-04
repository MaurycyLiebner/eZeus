#include "escholar.h"

#include "textures/egametextures.h"

eScholar::eScholar(eGameBoard& board) :
    eBasicPatroler(board, &eCharacterTextures::fScholar,
                   eCharacterType::scholar) {
    eGameTextures::loadScholar();
    setProvide(eProvide::gymnastScholar, 10000);
}
