#include "ehorsemanbase.h"

eHorsemanBase::eHorsemanBase(eGameBoard& board,
                             const eCharTexs charTexs,
                             const eCharacterType type) :
    eSoldier(board, charTexs, type) {
    setAttack(0.6);
    setSpeed(1.5);
}
