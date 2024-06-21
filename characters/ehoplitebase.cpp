#include "ehoplitebase.h"

eHopliteBase::eHopliteBase(eGameBoard& board,
                           const eCharTexs charTexs,
                           const eCharacterType type) :
    eSoldier(board, charTexs, type) {
    setAttack(0.5);
    setHP(500);
}
