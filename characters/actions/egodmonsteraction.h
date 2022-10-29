#ifndef EGODMONSTERACTION_H
#define EGODMONSTERACTION_H

#include "characters/echaracter.h"
#include "ecomplexaction.h"

#include "engine/boardData/eheatmaptask.h"
#include "engine/boardData/eheatmapdivisor.h"
#include "buildings/eheatgetters.h"

struct ePausedAction {
    eCharacterActionType fAt;
    stdsptr<eCharacterAction> fA;
    eOrientation fO;
};

class eGodMonsterAction : public eComplexAction {
public:
    using eComplexAction::eComplexAction;

    eTile* closestRoad(const int rdx, const int rdy) const;
    void moveAround(const eAction& finishAct = [](){},
                    const int time = 5000);
    using eFindFailFunc = std::function<void(eTile*)>;
    void goToTarget(const eHeatGetters::eHeatGetter hg,
                    const eFindFailFunc& findFailFunc);

    void pauseAction();
    void resumeAction();
private:
    std::vector<ePausedAction> mPausedActions;
};

#endif // EGODMONSTERACTION_H
