#ifndef ECHARACTERACTION_H
#define ECHARACTERACTION_H

class eDemeter;

class eCharacterAction {
public:
    eCharacterAction(eDemeter* const d);

    virtual void increment() = 0;
protected:
    eDemeter* const mCharacter;
};

#endif // ECHARACTERACTION_H
