#include "edionysushelpaction.h"

eDionysusHelpAction::eDionysusHelpAction(eCharacter* const c) :
    eProvideResourceHelpAction(c, eCharActionType::dionysusHelpAction,
                               eResourceType::wine, 16) {}

bool eDionysusHelpAction::sHelpNeeded(const eGameBoard& board) {
    return eProvideResourceHelpAction::sHelpNeeded(
                board, eResourceType::wine, 8);
}

