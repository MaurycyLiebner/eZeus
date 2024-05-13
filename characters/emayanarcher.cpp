#include "emayanarcher.h"

#include "textures/egametextures.h"

eMayanArcher::eMayanArcher(eGameBoard& board) :
    eArcherBase(board, &eCharacterTextures::fMayanArcher,
                eCharacterType::mayanArcher) {
    eGameTextures::loadMayanArcher();
}
