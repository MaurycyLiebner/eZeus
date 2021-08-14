#include "ewatchman.h"

eWatchman::eWatchman(eGameBoard& board) :
    eFightingPatroler(board, &eCharacterTextures::fWatchman,
                      eCharacterType::watchman) {}
