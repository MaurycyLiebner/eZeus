#ifndef ECHARACTERACTION_H
#define ECHARACTERACTION_H

class eCharacter;

enum class eCharacterActionState {
    running, finished, failed
};

class eCharacterAction {
public:
    eCharacterAction(eCharacter* const d);

    virtual void increment() = 0;

    eCharacter* character() const { return mCharacter; }
    eCharacterActionState state() const { return mState; }
protected:
    void setState(const eCharacterActionState state);

    eCharacter* const mCharacter;
private:
    eCharacterActionState mState{eCharacterActionState::running};
};

#endif // ECHARACTERACTION_H
