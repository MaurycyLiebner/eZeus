#include "eshepherd.h"

#include "textures/egametextures.h"

eShepherd::eShepherd(eGameBoard& board) :
    eShepherdBase(board, &eCharacterTextures::fShepherd,
                  eCharacterType::shepherd) {
    eGameTextures::loadShepherd();
}
