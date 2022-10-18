#ifndef ECOMPLEXACTION_H
#define ECOMPLEXACTION_H

#include "echaracteraction.h"

class eComplexAction : public eCharacterAction {
public:
    using eCharacterAction::eCharacterAction;

    virtual bool decide() { return false; };

    void increment(const int by);
protected:
    eCharacterAction* currentAction() const { return mCurrentAction.get(); }
    void setCurrentAction(const stdsptr<eCharacterAction>& a);
    void wait(const int t);
    void wait();
private:
    stdsptr<eCharacterAction> mCurrentAction;
};

#endif // ECOMPLEXACTION_H
