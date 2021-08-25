#ifndef ECOMPLEXACTION_H
#define ECOMPLEXACTION_H

#include "echaracteraction.h"

class eComplexAction : public eCharacterAction {
public:
    eComplexAction(eCharacter* const c,
                   const eAction& failAction,
                   const eAction& finishAction);

    void increment(const int by);
protected:
    eCharacterAction* currentAction() const { return mCurrentAction.get(); }
    void setCurrentAction(const stdsptr<eCharacterAction>& a);
private:
    stdsptr<eCharacterAction> mCurrentAction;
};

#endif // ECOMPLEXACTION_H
