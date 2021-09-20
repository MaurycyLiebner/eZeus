#include "ecomplexaction.h"

void eComplexAction::increment(const int by) {
    if(mCurrentAction) mCurrentAction->increment(by);
}

void eComplexAction::setCurrentAction(const stdsptr<eCharacterAction>& a) {
    mCurrentAction = a;
}
