#include "ewatchman.h"

#include "textures/egametextures.h"

eWatchman::eWatchman(eGameBoard& board) :
    eFightingPatroler(board, &eCharacterTextures::fWatchman,
                      eCharacterType::watchman) {
    eGameTextures::loadWatchman();
    setAttack(0.5);
    setHP(200);
}
