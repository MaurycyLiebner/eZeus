#include "ehealer.h"

#include "textures/egametextures.h"

eHealer::eHealer(eGameBoard& board) :
    eBasicPatroler(board, &eCharacterTextures::fHealer,
                   eCharacterType::healer) {
    eGameTextures::loadHealer();
}
