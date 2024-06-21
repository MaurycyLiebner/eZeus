#include "erockthrowerbase.h"

eRockThrowerBase::eRockThrowerBase(eGameBoard& board,
                                   const eCharTexs charTexs,
                                   const eCharacterType type) :
    eRangeSoldier(board, charTexs, type, 4) {
    setAttack(0.05);
    setHP(300);
}
