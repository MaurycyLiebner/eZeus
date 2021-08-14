#include "ethreadcharacter.h"

eThreadCharacter::eThreadCharacter(eCharacter* const character) {
    mType = character->type();
    mPlayerId = character->playerId();
    mHP = character->hp();
    mActionType = character->actionType();
}
