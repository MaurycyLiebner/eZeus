#include "eartemishelpaction.h"

eArtemisHelpAction::eArtemisHelpAction(eCharacter* const c) :
    eProvideResourceHelpAction(c, eCharActionType::artemisHelpAction,
                               eResourceType::meat, 32) {}

bool eArtemisHelpAction::sHelpNeeded(const eGameBoard& board) {
    return eProvideResourceHelpAction::sHelpNeeded(
                board, eResourceType::meat, 18);
}

