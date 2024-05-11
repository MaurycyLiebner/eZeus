#include "ehomeless.h"

#include "textures/egametextures.h"

eHomeless::eHomeless(eGameBoard& board) :
    eBasicPatroler(board, &eCharacterTextures::fHomeless,
                   eCharacterType::homeless) {
    eGameTextures::loadHomeless();
}
