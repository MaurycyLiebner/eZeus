#include "ecomplexaction.h"

eComplexAction::eComplexAction(
        eCharacter* const c,
        const eAction& failAction,
        const eAction& finishAction) :
    eCharacterAction(c, failAction, finishAction) {}

eComplexAction::~eComplexAction() {
    setCurrentAction(nullptr);
}

void eComplexAction::increment(const int by) {
    if(mCurrentAction) mCurrentAction->increment(by);
}

void eComplexAction::setCurrentAction(eCharacterAction* const a) {
    if(mCurrentAction) delete mCurrentAction;
    mCurrentAction = a;
}
