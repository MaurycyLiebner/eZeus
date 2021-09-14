#ifndef EGODVISITACTION_H
#define EGODVISITACTION_H

#include "ecomplexaction.h"

#include "characters/gods/egod.h"

class eGodVisitAction : public eComplexAction {
public:
    eGodVisitAction(eCharacter* const c,
                    const eAction& failAction,
                    const eAction& finishAction);

    void appear();
    void disappear();
    void moveAround();
    void patrol();

    eGodType type() const { return mType; }
private:
    const eGodType mType;
};

#endif // EGODVISITACTION_H
