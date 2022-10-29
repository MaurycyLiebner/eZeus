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

    void increment(const int by);
    bool decide();

    void goToTarget();
    void goBack();
private:
    void destroyBuilding(eBuilding* const b);
    eTile* closestEmptySpace(const int rdx, const int rdy) const;
    void randomPlaceOnBoard();
    std::function<bool(eTile* const)> obsticleHandler();
    bool lookForAttack(const int dtime, int& time,
                       const int freq, const int range);
    using eMonsterAct = std::function<eTile*(eTile* const t)>;
    using eTexPtr = eTextureCollection eDestructionTextures::*;
    bool lookForRangeAction(const int dtime,
                            int& time, const int freq,
                            const int range,
                            const eCharacterActionType at,
                            const eMonsterAct& act,
                            const eTexPtr missileTex,
                            const eFunc& missileSound,
                            const eFunc& finishMissileA);

    eTile* mHomeTile = nullptr;
    eMonsterAttackStage mStage{eMonsterAttackStage::none};
    const eMonsterType mType;
    int mLookForAttack = 0;
};

#endif // EMONSTERACTION_H
