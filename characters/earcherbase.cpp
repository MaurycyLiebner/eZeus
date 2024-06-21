#include "earcherbase.h"

eArcherBase::eArcherBase(eGameBoard& board,
                         const eCharTexs charTexs,
                         const eCharacterType type) :
    eSoldier(board, charTexs, type) {
    setRange(4);
    setAttack(0.05);
    setHP(300);
}
