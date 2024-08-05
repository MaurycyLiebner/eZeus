#include "earcherbase.h"

#include "enumbers.h"

eArcherBase::eArcherBase(eGameBoard& board,
                         const eCharTexs charTexs,
                         const eCharacterType type) :
    eSoldier(board, charTexs, type) {
    setRange(eNumbers::sArcherRange);
    setAttack(eNumbers::sArcherAttack);
    setHP(eNumbers::sArcherHP);
}
