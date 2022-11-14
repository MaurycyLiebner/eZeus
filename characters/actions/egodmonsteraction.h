#ifndef EGODMONSTERACTION_H
#define EGODMONSTERACTION_H

#include "characters/echaracter.h"
#include "ecomplexaction.h"

#include "engine/boardData/eheatmaptask.h"
#include "engine/boardData/eheatmapdivisor.h"
#include "buildings/eheatgetters.h"

#include "textures/egametextures.h"

#include "ewalkablehelpers.h"

struct ePausedAction {
    eCharacterActionType fAt;
    stdsptr<eCharacterAction> fA;
    eOrientation fO;
};

class eGodMonsterAction : public eComplexAction {
public:
    using eComplexAction::eComplexAction;

    void moveAround(const eAction& finishAct = [](){},
                    const int time = 5000);
    using eFindFailFunc = std::function<void(eTile*)>;
    using eObsticleHandler = std::function<bool(eTile* const)>;
    using eTileDistance = std::function<int(eTileBase* const)>;
    using eTileWalkable = std::function<bool(eTileBase* const)>;
    void goToTarget(const eHeatGetters::eHeatGetter hg,
                    const eFindFailFunc& findFailFunc,
                    const eObsticleHandler& oh = nullptr,
                    const eTileDistance& tileDistance = nullptr,
                    const eTileWalkable& pathFindWalkable =
                        eWalkableObject::sCreateDefault(),
                    const eTileWalkable& moveWalkable = nullptr);

    using eTexPtr = eTextureCollection eDestructionTextures::*;
    using eFunc = std::function<void()>;
    void spawnMissile(const eCharacterActionType at,
                      const eTexPtr tex,
                      const int attackTime,
                      eTile* const target,
                      const eFunc& playSound,
                      const eFunc& finishMissileA,
                      const eFunc& finishAttackA = nullptr);
    void spawnMultipleMissiles(const eCharacterActionType at,
                               const eTexPtr tex,
                               const int attackTime,
                               eTile* const target,
                               const eFunc& playSound,
                               const eFunc& playHitSound,
                               const eFunc& finishA,
                               const int nMissiles);
    void spawnTimedMissiles(const eCharacterActionType at,
                            const eTexPtr tex,
                            const int attackTime,
                            eTile* const target,
                            const eFunc& playSound,
                            const eFunc& playHitSound,
                            const eFunc& finishA,
                            const int time);

    void pauseAction();
    void resumeAction();
private:
    std::vector<ePausedAction> mPausedActions;
};

#endif // EGODMONSTERACTION_H
