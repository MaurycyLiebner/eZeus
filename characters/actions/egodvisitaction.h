#ifndef EGODVISITACTION_H
#define EGODVISITACTION_H

#include "egodaction.h"

enum class eGodVisitStage {
    none, appear, patrol, disappear
};

class eGodVisitAction : public eGodAction {
public:
    using eGodAction::eGodAction;

    bool decide();
private:
    eGodVisitStage mStage{eGodVisitStage::none};
};

#endif // EGODVISITACTION_H
