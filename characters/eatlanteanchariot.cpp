#include "eatlanteanchariot.h"

#include "textures/echaractertextures.h"
#include "textures/egametextures.h"

eAtlanteanChariot::eAtlanteanChariot(eGameBoard& board) :
    eChariotBase(board, &eCharacterTextures::fAtlanteanChariot,
                 eCharacterType::atlanteanChariot) {
    eGameTextures::loadAtlanteanChariot();
}
