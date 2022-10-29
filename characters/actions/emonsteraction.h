#ifndef EMONSTERACTION_H
#define EMONSTERACTION_H

#include "egodmonsteraction.h"

#include "characters/monsters/emonster.h"

enum class eMonsterAttackStage {
    none, wait, attack, goBack
};

class eMonsterAction : public eGodMonsterAction {
public:
    eMonsterAction(eCharacter* const c,
                   const eAction& failAction,
                   const eAction& finishAction);

    bool decide();

    void goToTarget();
    void goBack();
private:
    void destroyBuilding(eBuilding* const b);
    eTile* closestEmptySpace(const int rdx, const int rdy) const;
    void randomPlaceOnBoard();
    std::function<bool(eTile* const)> obsticleHandler();

    eTile* mHomeTile = nullptr;
    eMonsterAttackStage mStage{eMonsterAttackStage::none};
    const eMonsterType mType;
};

#endif // EMONSTERACTION_H
