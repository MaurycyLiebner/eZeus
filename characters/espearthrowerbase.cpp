#include "espearthrowerbase.h"

#include "enumbers.h"

eSpearthrowerBase::eSpearthrowerBase(eGameBoard& board,
                                     const eCharTexs charTexs,
                                     const eCharacterType type) :
    eSoldier(board, charTexs, type) {
    setRange(eNumbers::sSpearthrowerRange);
    setAttack(eNumbers::sSpearthrowerAttack);
    setHP(eNumbers::sSpearthrowerHP);
}
