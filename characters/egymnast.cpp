#include "egymnast.h"

#include "textures/egametextures.h"

eGymnast::eGymnast(eGameBoard& board) :
    eBasicPatroler(board, &eCharacterTextures::fGymnast,
                   eCharacterType::gymnast) {
    eGameTextures::loadGymnast();
    setProvide(eProvide::gymnast, 10000);
}
