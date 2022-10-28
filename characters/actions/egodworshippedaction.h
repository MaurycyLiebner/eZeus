#ifndef EGODWORSHIPPEDACTION_H
#define EGODWORSHIPPEDACTION_H

#include "egodaction.h"

enum class eGodWorshippedStage {
    none, appear, goTo1, patrol1, goTo2, patrol2, disappear
};

class eGodWorshippedAction : public eGodAction {
public:
    using eGodAction::eGodAction;

    void increment(const int by);
    bool decide();
private:
    eGodWorshippedStage mStage{eGodWorshippedStage::none};

    int mLookForBless = 0;
    int mLookForSoldierAttack = 0;
};

#endif // EGODWORSHIPPEDACTION_H
