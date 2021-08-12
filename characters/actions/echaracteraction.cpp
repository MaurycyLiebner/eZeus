#include "echaracteraction.h"

#include "characters/echaracter.h"

eCharacterAction::eCharacterAction(eCharacter* const c,
                                   const eAction& failAction,
                                   const eAction& finishAction) :
    mCharacter(c),
    mFailAction(failAction),
    mFinishAction(finishAction) {

}

void eCharacterAction::pause() {
    mPauseType = mCharacter->actionType();
}

void eCharacterAction::resume() {
    mCharacter->setActionType(mPauseType);
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
