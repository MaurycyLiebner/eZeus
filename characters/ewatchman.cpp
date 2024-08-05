#include "ewatchman.h"

#include "textures/egametextures.h"
#include "enumbers.h"

eWatchman::eWatchman(eGameBoard& board) :
    eFightingPatroler(board, &eCharacterTextures::fWatchman,
                      eCharacterType::watchman) {
    eGameTextures::loadWatchman();
    setProvide(eProvide::satisfaction, 100000);
    setAttack(eNumbers::sWatchmanAttack);
    setHP(eNumbers::sWatchmanHP);
}
