#include "ewaitaction.h"

eWaitAction::eWaitAction(eCharacter* const c) :
    eCharacterAction(c, eCharActionType::waitAction) {}

void eWaitAction::setTime(const int t) {
    mRemTime = t;
}

void eWaitAction::increment(const int by) {
    mRemTime -= by;
    if(mRemTime <= 0) {
        setState(eCharacterActionState::finished);
    }
}

void eWaitAction::read(eReadStream& src) {
    eCharacterAction::read(src);
    src >> mRemTime;
}

void eWaitAction::write(eWriteStream& dst) const {
    eCharacterAction::write(dst);
    dst << mRemTime;
}
