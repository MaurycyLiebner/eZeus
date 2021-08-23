#ifndef ECOMPLEXACTION_H
#define ECOMPLEXACTION_H

#include "echaracteraction.h"

class eComplexAction : public eCharacterAction {
public:
    eComplexAction(eCharacter* const c,
                   const eAction& failAction,
                   const eAction& finishAction);
    ~eComplexAction();

    void increment(const int by);
protected:
    eCharacterAction* currentAction() const { return mCurrentAction; }
    void setCurrentAction(eCharacterAction* const a);
private:
    eCharacterAction* mCurrentAction = nullptr;
};

#endif // ECOMPLEXACTION_H
