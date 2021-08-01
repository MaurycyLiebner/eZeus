#ifndef ECHARACTERACTION_H
#define ECHARACTERACTION_H

#include <functional>

class eCharacter;

enum class eCharacterActionState {
    running, finished, failed
};

using eAction = std::function<void()>;

class eCharacterAction {
public:
    eCharacterAction(eCharacter* const d,
                     const eAction& failAction,
                     const eAction& finishAction);

    virtual void increment() = 0;

    eCharacter* character() const { return mCharacter; }
    eCharacterActionState state() const { return mState; }
protected:
    void setState(const eCharacterActionState state);

    eCharacter* const mCharacter;
private:
    eCharacterActionState mState{eCharacterActionState::running};
    const eAction mFailAction;
    const eAction mFinishAction;
};

#endif // ECHARACTERACTION_H
