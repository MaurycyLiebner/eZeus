#ifndef ECHARACTERACTION_H
#define ECHARACTERACTION_H

#include <functional>

class eCharacter;

enum class eCharacterActionState {
    running, finished, failed
};

enum class eCharacterActionType {
    walk,
    fight,
    die,
    collect,
    carry
};

using eAction = std::function<void()>;

class eCharacterAction {
public:
    eCharacterAction(eCharacter* const c,
                     const eAction& failAction,
                     const eAction& finishAction);
    virtual ~eCharacterAction() {}

    virtual void increment(const int by) = 0;
    virtual void pause();
    virtual void resume();

    eCharacter* character() const { return mCharacter; }
    eCharacterActionState state() const { return mState; }
protected:
    void setState(const eCharacterActionState state);

    eCharacter* const mCharacter;
private:
    eCharacterActionState mState{eCharacterActionState::running};
    const eAction mFailAction;
    const eAction mFinishAction;
    eCharacterActionType mPauseType;
};

#endif // ECHARACTERACTION_H
