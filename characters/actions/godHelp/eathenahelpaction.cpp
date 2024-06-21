#include "eathenahelpaction.h"

eAthenaHelpAction::eAthenaHelpAction(eCharacter* const c) :
    eProvideResourceHelpAction(c, eCharActionType::athenaHelpAction,
                               eResourceType::oliveOil, 16) {}

bool eAthenaHelpAction::sHelpNeeded(const eGameBoard& board) {
    return eProvideResourceHelpAction::sHelpNeeded(
                board, eResourceType::oliveOil, 8);
}

