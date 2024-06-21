#ifndef EARTEMISHELPACTION_H
#define EARTEMISHELPACTION_H

#include "eprovideresourcehelpaction.h"

class eArtemisHelpAction : public eProvideResourceHelpAction {
public:
    eArtemisHelpAction(eCharacter* const c);

    static bool sHelpNeeded(const eGameBoard& board);
};

#endif // EARTEMISHELPACTION_H
