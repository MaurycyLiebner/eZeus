#include "epersianarcher.h"

#include "textures/egametextures.h"

ePersianArcher::ePersianArcher(eGameBoard& board) :
    eArcherBase(board, &eCharacterTextures::fPersianArcher,
                eCharacterType::persianArcher) {
    eGameTextures::loadPersianArcher();
}
