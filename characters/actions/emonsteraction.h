#ifndef EMONSTERACTION_H
#define EMONSTERACTION_H

#include "egodmonsteraction.h"

#include "characters/monsters/emonster.h"

enum class eMonsterAttackStage {
    none, wait, attack
};

class eMonsterAction : public eGodMonsterAction {
public:
    eMonsterAction(eCharacter* const c,
                   const eAction& failAction,
                   const eAction& finishAction);

    void increment(const int by);
    bool decide();

    void goToTarget();
private:
    void randomPlaceOnBoard();

    eMonsterAttackStage mStage{eMonsterAttackStage::none};
    const eMonsterType mType;
};

#endif // EMONSTERACTION_H
