#ifndef EWAITACTION_H
#define EWAITACTION_H

#include "echaracteraction.h"

class eWaitAction : public eCharacterAction {
public:
    using eCharacterAction::eCharacterAction;

    void increment(const int) {}
};

#endif // EWAITACTION_H
