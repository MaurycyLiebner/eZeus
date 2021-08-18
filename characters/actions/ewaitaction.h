#ifndef EWAITACTION_H
#define EWAITACTION_H

#include "echaracteraction.h"

class eWaitAction : public eCharacterAction {
public:
    using eCharacterAction::eCharacterAction;

    void increment(const int by);

    void setTime(const int t);
private:
    int mRemTime{__INT_MAX__};
};

#endif // EWAITACTION_H
