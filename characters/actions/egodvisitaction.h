#ifndef EGODVISITACTION_H
#define EGODVISITACTION_H

#include "ecomplexaction.h"

class eGodVisitAction : public eComplexAction {
public:
    using eComplexAction::eComplexAction;

    void appear();
    void disappear();
    void moveAround();
    void patrol();
};

#endif // EGODVISITACTION_H
