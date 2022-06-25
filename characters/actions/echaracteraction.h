#ifndef ECHARACTERACTION_H
#define ECHARACTERACTION_H

#include <functional>

#include "echaracteractiontype.h"
#include "pointers/estdselfref.h"

class eCharacter;

enum class eCharacterActionState {
    running, finished, failed
};

using eAction = std::function<void()>;

class eCharacterAction : public eStdSelfRef {
public:
    eCharacterAction(eCharacter* const c,
                     const eAction& failAction,
                     const eAction& finishAction);
    virtual ~eCharacterAction();

    virtual void increment(const int by) = 0;
    virtual void pause();
    virtual void resume();

    eCharacter* character() const { return mCharacter; }
    eCharacterActionState state() const { return mState; }
    void setState(const eCharacterActionState state);

    void setDeleteFailAction(const eAction& d);
private:
    eCharacter* const mCharacter;
    eCharacterActionState mState{eCharacterActionState::running};
    const eAction mFailAction;
    const eAction mFinishAction;
    eAction mDeleteFailAction;
    eCharacterActionType mPauseType;
};

#endif // ECHARACTERACTION_H
