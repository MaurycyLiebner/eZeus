#include "ecomplexaction.h"

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
