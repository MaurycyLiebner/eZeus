#include "echaracteraction.h"

eCharacterAction::eCharacterAction(eCharacter* const d,
                                   const eAction& failAction,
                                   const eAction& finishAction) :
    mCharacter(d),
    mFailAction(failAction),
    mFinishAction(finishAction) {

}

void eCharacterAction::setState(const eCharacterActionState state) {
    if(state == mState) return;
    mState = state;
    if(mState == eCharacterActionState::failed) {
        if(mFailAction) mFailAction();
    } else if(mState == eCharacterActionState::finished) {
        if(mFinishAction) mFinishAction();
    }
}
