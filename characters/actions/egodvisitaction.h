#ifndef EGODVISITACTION_H
#define EGODVISITACTION_H

#include "egodaction.h"

enum class eGodVisitStage {
    none, appear, patrol, disappear
};

class eGodVisitAction : public eGodAction {
public:
    using eGodAction::eGodAction;

    void increment(const int by);
    bool decide();
private:
    eGodVisitStage mStage{eGodVisitStage::none};

    int mLookForBless = 0;
    int mLookForSoldierAttack = 0;
};

#endif // EGODVISITACTION_H
