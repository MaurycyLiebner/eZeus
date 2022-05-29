#ifndef EGODVISITACTION_H
#define EGODVISITACTION_H

#include "ecomplexaction.h"

#include "characters/gods/egod.h"

enum class eGodVisitStage {
    none, appear, patrol, disappear
};

class eGodVisitAction : public eComplexAction {
public:
    eGodVisitAction(eCharacter* const c,
                    const eAction& failAction,
                    const eAction& finishAction);

    bool decide();

    void placeOnBoard();
    void appear();
    void run();
    void disappear();
    void moveAround(const eAction& finishAct = [](){},
                    const int time = 5000);
    void patrol(const eAction& finishAct = [](){},
                const int dist = 100);

    eGodType type() const { return mType; }
private:
    const eGodType mType;
    eGodVisitStage mStage{eGodVisitStage::none};
};

#endif // EGODVISITACTION_H
