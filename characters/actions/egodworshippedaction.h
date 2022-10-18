#ifndef EGODWORSHIPPEDACTION_H
#define EGODWORSHIPPEDACTION_H

#include "egodaction.h"

enum class eGodWorshippedStage {
    none, appear, goTo, patrol, disappear
};

class eGodWorshippedAction : public eGodAction {
public:
    using eGodAction::eGodAction;

    bool decide();
private:
    void teleport(eTile* const tile);
    void goTo();

    eGodWorshippedStage mStage{eGodWorshippedStage::none};
};

#endif // EGODWORSHIPPEDACTION_H
