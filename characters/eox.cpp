#include "eox.h"

#include "textures/egametextures.h"

eOx::eOx(eGameBoard& board) :
    eBasicPatroler(board, &eCharacterTextures::fOx,
                   eCharacterType::ox) {
    eGameTextures::loadOx();
}
