#include "ewatchman.h"

#include "textures/egametextures.h"

eWatchman::eWatchman(eGameBoard& board) :
    eFightingPatroler(board, &eCharacterTextures::fWatchman,
                      eCharacterType::watchman) {
    eGameTextures::loadWatchman();
    setProvide(eProvide::satisfaction, 100000);
    setAttack(0.5);
    setHP(200);
}
