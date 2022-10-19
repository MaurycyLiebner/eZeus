#ifndef EGODWORSHIPPEDACTION_H
#define EGODWORSHIPPEDACTION_H

#include "egodaction.h"

enum class eGodWorshippedStage {
    none, appear, goTo, patrol, disappear
};

class eGodWorshippedAction : public eGodAction {
public:
    using eGodAction::eGodAction;

    void increment(const int by);
    bool decide();
private:
    void goTo();

    eGodWorshippedStage mStage{eGodWorshippedStage::none};

    int mLookForBless = 0;
};

#endif // EGODWORSHIPPEDACTION_H
