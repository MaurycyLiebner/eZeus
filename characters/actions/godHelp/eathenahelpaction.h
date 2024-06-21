#ifndef EATHENAHELPACTION_H
#define EATHENAHELPACTION_H

#include "eprovideresourcehelpaction.h"

class eAthenaHelpAction : public eProvideResourceHelpAction {
public:
    eAthenaHelpAction(eCharacter* const c);

    static bool sHelpNeeded(const eGameBoard& board);
};

#endif // EATHENAHELPACTION_H
