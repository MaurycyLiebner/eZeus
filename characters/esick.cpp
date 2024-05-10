#include "esick.h"

#include "textures/egametextures.h"

eSick::eSick(eGameBoard& board) :
    eFightingPatroler(board, &eCharacterTextures::fSick,
                      eCharacterType::sick) {
    eGameTextures::loadSick();
    setSpeed(0.35);
}
