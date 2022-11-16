#ifndef EGODVISITACTION_H
#define EGODVISITACTION_H

#include "egodaction.h"

enum class eGodVisitStage {
    none, appear, patrol, disappear
};

class eGodVisitAction : public eGodAction {
public:
    eGodVisitAction(eCharacter* const c);

    void increment(const int by) override;
    bool decide() override;

    void read(eReadStream& src) override;
    void write(eWriteStream& dst) const override;
private:
    eGodVisitStage mStage{eGodVisitStage::none};

    int mLookForBless = 0;
    int mLookForSoldierAttack = 0;
};

#endif // EGODVISITACTION_H
