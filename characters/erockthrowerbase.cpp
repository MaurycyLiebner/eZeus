#include "erockthrowerbase.h"

eRockThrowerBase::eRockThrowerBase(eGameBoard& board,
                                   const eCharTexs charTexs) :
    eRangeSoldier(board, charTexs, eCharacterType::rockThrower, 4) {
    setAttack(0.05);
    setHP(300);
}
