#include "echaracteraction.h"

#include "engine/egameboard.h"
#include "characters/echaracter.h"

eCharacterAction::eCharacterAction(
        eCharacter* const c, const eCharActionType type) :
    mBoard(c->getBoard()), mCharacter(c), mType(type) {
    mBoard.registerCharacterAction(this);
}

eCharacterAction::~eCharacterAction() {
    mBoard.unregisterCharacterAction(this);
    if(mState == eCharacterActionState::running) {
        if(mDeleteFailAction) mDeleteFailAction->call();
    }
}

void eCharacterAction::setState(const eCharacterActionState state) {
    if(state == mState) return;
    mState = state;
    if(mState == eCharacterActionState::failed) {
        if(mFailAction) mFailAction->call();
    } else if(mState == eCharacterActionState::finished) {
        if(mFinishAction) mFinishAction->call();
    }
}

void eCharacterAction::setFinishAction(const stdsptr<eCharActFunc>& f) {
    mFinishAction = f;
}

void eCharacterAction::setFailAction(const stdsptr<eCharActFunc>& f) {
    mFailAction = f;
}

void eCharacterAction::setDeleteFailAction(const stdsptr<eCharActFunc>& d) {
    mDeleteFailAction = d;
}

void eCharacterAction::read(eReadStream& src) {
    src >> mIOID;

    src >> mState;
    src >> mPauseType;

    mFinishAction = src.readCharActFunc(board());
    mFailAction = src.readCharActFunc(board());
    mDeleteFailAction = src.readCharActFunc(board());
}

void eCharacterAction::write(eWriteStream& dst) const {
    dst << mIOID;

    dst << mState;
    dst << mPauseType;

    dst.writeCharActFunc(mFinishAction.get());
    dst.writeCharActFunc(mFailAction.get());
    dst.writeCharActFunc(mDeleteFailAction.get());
}
