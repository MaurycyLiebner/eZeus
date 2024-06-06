#include "ebutcher.h"

#include "textures/egametextures.h"

eButcher::eButcher(eGameBoard& board) :
    eBasicPatroler(board, &eCharacterTextures::fButcher,
                   eCharacterType::butcher) {
    eGameTextures::loadButcher();
}
