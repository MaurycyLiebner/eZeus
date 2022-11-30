#include "edonkey.h"

#include "textures/egametextures.h"

eDonkey::eDonkey(eGameBoard& board) :
    eBasicPatroler(board, &eCharacterTextures::fDonkey,
                   eCharacterType::donkey) {
    eGameTextures::loadDonkey();
}
