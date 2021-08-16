#include "ethreadcharacter.h"

eThreadCharacter::eThreadCharacter() :
    eCharacterBase(eCharacterType::none) {}

void eThreadCharacter::load(eCharacterBase* const character) {
    setType(character->type());
    setPlayerId(character->playerId());
    setHP(character->hp());
    setActionType(character->actionType());
}
