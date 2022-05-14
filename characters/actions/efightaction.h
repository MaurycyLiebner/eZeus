#ifndef EFIGHTACTION_H
#define EFIGHTACTION_H

#include "echaracteraction.h"
#include "characters/echaracter.h"

class eFightAction : public eCharacterAction {
public:
    eFightAction(eCharacter* const c,
                 eCharacter* const o,
                 const eAction& finishAction);

    void increment(const int by);
private:
    const stdptr<eCharacter> mOpponent;

    int mTime = 0;
};

#endif // EFIGHTACTION_H
