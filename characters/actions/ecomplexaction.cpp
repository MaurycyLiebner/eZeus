#include "ecomplexaction.h"

#include "ewaitaction.h"

void eComplexAction::increment(const int by) {
    if(mCurrentAction) {
        const auto state = mCurrentAction->state();
        if(state == eCharacterActionState::running) {
            mCurrentAction->increment(by);
            return;
        } else {
            mCurrentAction = nullptr;
            decide();
        }
    } else {
        decide();
    }
}

void eComplexAction::setCurrentAction(const stdsptr<eCharacterAction>& a) {
    mCurrentAction = a;
}

void eComplexAction::wait(const int t) {
    const auto w = e::make_shared<eWaitAction>(
                       character(), [](){}, [](){});
    w->setTime(t);
    setCurrentAction(w);
}
