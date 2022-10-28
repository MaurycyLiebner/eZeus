#include "emonster.h"

#include "ecalydonianboar.h"

eMonster::eMonster(eGameBoard& board, const eMonsterType mt) :
    eCharacter(board, sMonsterToCharacterType(mt)) {}

eMonsterType eMonster::sCharacterToMonsterType(const eCharacterType type,
                                   bool* const valid) {
    if(valid) *valid = true;
    switch(type) {
    case eCharacterType::calydonianBoar: return eMonsterType::calydonianBoar;
    default:
        if(valid) *valid = false;
        return eMonsterType::calydonianBoar;
    }
}

eCharacterType eMonster::sMonsterToCharacterType(const eMonsterType type) {
    switch(type) {
    case eMonsterType::calydonianBoar: return eCharacterType::calydonianBoar;
    default: return eCharacterType::calydonianBoar;
    }
}

stdsptr<eMonster> eMonster::sCreateMonster(const eMonsterType type, eGameBoard& board) {
    switch(type) {
    case eMonsterType::calydonianBoar:
        return e::make_shared<eCalydonianBoar>(board);
    }
}
