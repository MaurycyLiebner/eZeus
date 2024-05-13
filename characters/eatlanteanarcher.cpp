#include "eatlanteanarcher.h"

#include "textures/egametextures.h"

eAtlanteanArcher::eAtlanteanArcher(eGameBoard& board) :
    eArcherBase(board, &eCharacterTextures::fAtlanteanArcher,
                eCharacterType::atlanteanArcher) {
    eGameTextures::loadAtlanteanArcher();
}
