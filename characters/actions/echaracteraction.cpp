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

    {
        bool hasFinish;
        src >> hasFinish;
        if(hasFinish) {
            eCharActFuncType type;
            src >> type;
            const auto f = eCharActFunc::sCreate(board(), type);
            f->read(src);
            setFinishAction(f);
        }
    }
    {
        bool hasFail;
        src >> hasFail;
        if(hasFail) {
            eCharActFuncType type;
            src >> type;
            const auto f = eCharActFunc::sCreate(board(), type);
            f->read(src);
            setFailAction(f);
        }
    }
    {
        bool hasDeleteFail;
        src >> hasDeleteFail;
        if(hasDeleteFail) {
            eCharActFuncType type;
            src >> type;
            const auto f = eCharActFunc::sCreate(board(), type);
            f->read(src);
            setDeleteFailAction(f);
        }
    }
}

void eCharacterAction::write(eWriteStream& dst) const {
    dst << mIOID;

    dst << mState;
    dst << mPauseType;
    {
        const bool hasFinish = mFinishAction != nullptr;
        dst << hasFinish;
        if(hasFinish) {
            dst << mFinishAction->type();
            mFinishAction->write(dst);
        }
    }
    {
        const bool hasFail = mFailAction != nullptr;
        dst << hasFail;
        if(hasFail) {
            dst << mFailAction->type();
            mFailAction->write(dst);
        }
    }
    {
        const bool hasDeleteFail = mDeleteFailAction != nullptr;
        dst << hasDeleteFail;
        if(hasDeleteFail) {
            dst << mDeleteFailAction->type();
            mDeleteFailAction->write(dst);
        }
    }
}
