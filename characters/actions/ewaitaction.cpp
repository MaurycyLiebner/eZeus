#include "ewaitaction.h"

void eWaitAction::setTime(const int t) {
    mRemTime = t;
}

void eWaitAction::increment(const int by) {
    mRemTime -= by;
    if(mRemTime <= 0) {
        setState(eCharacterActionState::finished);
    }
}
