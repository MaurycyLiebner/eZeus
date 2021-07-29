#ifndef ECHARACTERACTION_H
#define ECHARACTERACTION_H

class eDemeter;

class eCharacterAction {
public:
    eCharacterAction();

    virtual void increment(eDemeter* const d) = 0;
private:
};

#endif // ECHARACTERACTION_H
