#ifndef ECOMPLEXACTION_H
#define ECOMPLEXACTION_H

#include "echaracteraction.h"

class eComplexAction : public eCharacterAction {
public:
    using eCharacterAction::eCharacterAction;

    virtual bool decide() = 0;

    void increment(const int by) override;

    void read(eReadStream& src) override;
    void write(eWriteStream& dst) const override;

    eCharacterAction* currentAction() const { return mCurrentAction.get(); }
    void setCurrentAction(const stdsptr<eCharacterAction>& a);
protected:
    void wait(const int t);
    void wait();
private:
    stdsptr<eCharacterAction> mCurrentAction;
};

#endif // ECOMPLEXACTION_H
