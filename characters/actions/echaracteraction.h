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
protected:
    eCharacter* const mCharacter;
};

#endif // ECHARACTERACTION_H
