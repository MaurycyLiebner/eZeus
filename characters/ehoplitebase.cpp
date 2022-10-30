#include "ehoplitebase.h"

eHopliteBase::eHopliteBase(eGameBoard& board,
                           const eCharTexs charTexs) :
    eSoldier(board, charTexs, eCharacterType::hoplite) {
    setAttack(0.5);
    setHP(500);
}
