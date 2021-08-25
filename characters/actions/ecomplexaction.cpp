#include "ecomplexaction.h"

eComplexAction::eComplexAction(
        eCharacter* const c,
        const eAction& failAction,
        const eAction& finishAction) :
    eCharacterAction(c, failAction, finishAction) {}

void eComplexAction::increment(const int by) {
    if(mCurrentAction) mCurrentAction->increment(by);
}

void eComplexAction::setCurrentAction(const stdsptr<eCharacterAction>& a) {
    mCurrentAction = a;
}
