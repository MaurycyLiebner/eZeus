#ifndef EFIGHTACTION_H
#define EFIGHTACTION_H

#include "echaracteraction.h"

class eFightAction : public eCharacterAction {
public:
    eFightAction(eCharacter* const c,
                 eCharacter* const o,
                 const eAction& finishAction);

    void increment(const int by);
private:
    eCharacter* const mOpponent;

    int mTime = 0;
};

#endif // EFIGHTACTION_H
