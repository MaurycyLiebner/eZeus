#ifndef EMONSTER_H
#define EMONSTER_H

#include "characters/echaracter.h"

enum class eMonsterType {
    calydonianBoar
};

class eMonster : public eCharacter {
public:
    eMonster(eGameBoard& board, const eMonsterType mt);

    static eMonsterType sCharacterToMonsterType(
            const eCharacterType type, bool* const valid = nullptr);
    static eCharacterType sMonsterToCharacterType(
            const eMonsterType type);
    static stdsptr<eMonster> sCreateMonster(
            const eMonsterType type, eGameBoard& board);
};

#endif // EMONSTER_H
