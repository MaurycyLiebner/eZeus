#include "ehorsemanbase.h"

#include "enumbers.h"

eHorsemanBase::eHorsemanBase(eGameBoard& board,
                             const eCharTexs charTexs,
                             const eCharacterType type) :
    eSoldier(board, charTexs, type) {
    setAttack(eNumbers::sHorsemanAttack);
    setSpeed(eNumbers::sHorsemanSpeed);
    setHP(eNumbers::sHorsemanHP);
}
