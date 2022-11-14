#include "ecomplexaction.h"

#include "ewaitaction.h"

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

void eComplexAction::read(eReadStream& src) {
    eCharacterAction::read(src);
    bool hasAction;
    src >> hasAction;
    if(hasAction) {
        eCharActionType type;
        src >> type;
        mCurrentAction = eCharacterAction::sCreate(character(), type);
        mCurrentAction->read(src);
    }
}

void eComplexAction::write(eWriteStream& dst) const {
    eCharacterAction::write(dst);
    dst << (mCurrentAction != nullptr);
    if(mCurrentAction) {
        dst << mCurrentAction->type();
        mCurrentAction->write(dst);
    }
}

void eComplexAction::setCurrentAction(const stdsptr<eCharacterAction>& a) {
    mCurrentAction = a;
}

void eComplexAction::wait(const int t) {
    const auto w = e::make_shared<eWaitAction>(
                       character(), [](){}, [](){});
    w->setTime(t);
    setCurrentAction(w);
}

void eComplexAction::wait() {
    const auto w = e::make_shared<eWaitAction>(
                       character(), [](){}, [](){});
    setCurrentAction(w);
}
