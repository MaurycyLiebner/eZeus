#include "ecentaurarcher.h"

#include "textures/egametextures.h"

eCentaurArcher::eCentaurArcher(eGameBoard& board) :
    eArcherBase(board, &eCharacterTextures::fCentaurArcher,
                eCharacterType::centaurArcher) {
    eGameTextures::loadCentaurArcher();
    setSpeed(1.5);
}
