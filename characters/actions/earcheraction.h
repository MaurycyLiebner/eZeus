#ifndef EARCHERACTION_H
#define EARCHERACTION_H

#include "ecomplexaction.h"

class eArcherAction : public eComplexAction {
public:
    using eComplexAction::eComplexAction;

    void increment(const int by);
};

#endif // EARCHERACTION_H
