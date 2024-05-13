#include "eegyptianarcher.h"

#include "textures/egametextures.h"

eEgyptianArcher::eEgyptianArcher(eGameBoard& board) :
    eArcherBase(board, &eCharacterTextures::fEgyptianArcher,
                eCharacterType::egyptianArcher) {
    eGameTextures::loadEgyptianArcher();
}
