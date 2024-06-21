#ifndef EDIONYSUSHELPACTION_H
#define EDIONYSUSHELPACTION_H

#include "eprovideresourcehelpaction.h"

class eDionysusHelpAction : public eProvideResourceHelpAction {
public:
    eDionysusHelpAction(eCharacter* const c);

    static bool sHelpNeeded(const eGameBoard& board);
};

#endif // EDIONYSUSHELPACTION_H
