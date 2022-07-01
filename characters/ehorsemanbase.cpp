#include "ehorsemanbase.h"

eHorsemanBase::eHorsemanBase(eGameBoard& board,
                             const eCharTexs charTexs) :
    eSoldier(board, charTexs, eCharacterType::horseman) {
    setAttack(0.6);
    setSpeed(1.5);
}
