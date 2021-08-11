#ifndef EDIEACTION_H
#define EDIEACTION_H

#include "echaracteraction.h"

class eDieAction : public eCharacterAction {
public:
    eDieAction(eCharacter* const c,
               const eAction& finishAction);

    void increment(const int by);
private:
    int mTime = 0;
};

#endif // EDIEACTION_H
