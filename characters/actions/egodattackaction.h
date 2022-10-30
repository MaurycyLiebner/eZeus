#ifndef EGODATTACKACTION_H
#define EGODATTACKACTION_H

#include "egodaction.h"

enum class eGodAttackStage {
    none, appear, goTo1, patrol1, goTo2, patrol2, disappear
};

class eGodAttackAction : public eGodAction {
public:
    using eGodAction::eGodAction;

    void increment(const int by);
    bool decide();
private:

    bool lookForAttack(const int dtime, int& time,
                       const int freq, const int range);

    bool lookForGodAttack(const int dtime, int& time,
                          const int freq, const int range);
    void goToTarget();
    std::function<bool(eTile* const)> obsticleHandler();
    void destroyBuilding(eBuilding* const b);

    eGodAttackStage mStage{eGodAttackStage::none};

    int mLookForCurse = 0;
    int mLookForAttack = 0;
    int mLookForGod = 0;
};

#endif // EGODATTACKACTION_H
