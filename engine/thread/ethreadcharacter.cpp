#include "ethreadcharacter.h"

void eThreadCharacter::load(eCharacter* const character) {
    mType = character->type();
    mPlayerId = character->playerId();
    mHP = character->hp();
    mActionType = character->actionType();
}
