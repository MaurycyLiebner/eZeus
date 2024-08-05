#include "erockthrowerbase.h"

#include "enumbers.h"

eRockThrowerBase::eRockThrowerBase(eGameBoard& board,
                                   const eCharTexs charTexs,
                                   const eCharacterType type) :
    eRangeSoldier(board, charTexs, type, eNumbers::sRabbleRange) {
    setAttack(eNumbers::sRabbleAttack);
    setHP(eNumbers::sRabbleHP);
}
