#ifndef EGODACTION_H
#define EGODACTION_H

#include "ecomplexaction.h"

#include "characters/gods/egod.h"

class eDestructionTextures;
enum class eGodSound;

struct ePausedAction {
    eCharacterActionType fAt;
    stdsptr<eCharacterAction> fA;
    eOrientation fO;
};

class eGodAction : public eComplexAction {
public:
    eGodAction(eCharacter* const c,
               const eAction& failAction,
               const eAction& finishAction);

    using eFunc = std::function<void()>;
    void appear(const eFunc& finish = nullptr);
    void disappear(const bool die = false,
                   const eFunc& finish = nullptr);
    void teleport(eTile* const tile);

    void moveAround(const eAction& finishAct = [](){},
                    const int time = 5000);
    void patrol(const eAction& finishAct = [](){},
                const int dist = 100);

    void randomPlaceOnBoard();
    eTile* closestRoad(const int rdx, const int rdy) const;

    using eGodAct = std::function<eTile*(eTile* const t)>;
    using eTexPtr = eTextureCollection eDestructionTextures::*;
    bool lookForRangeAction(const int dtime,
                            int& time, const int freq,
                            const int range,
                            const eCharacterActionType at,
                            const eGodAct& act,
                            const eTexPtr missileTex,
                            const eGodSound missileSound,
                            const eFunc& finishMissileA);
    bool lookForBlessCurse(const int dtime, int& time,
                           const int freq, const int range,
                           const double bless);

    void spawnGodMissile(const eCharacterActionType at,
                         const eTexPtr tex,
                         eTile* const target,
                         const eGodSound sound,
                         const eFunc& finishMissileA,
                         const eFunc& finishAttackA = nullptr);
    void spawnGodMultipleMissiles(
            const eCharacterActionType at,
            const eTexPtr tex,
            eTile* const target,
            const eGodSound sound,
            const eFunc& finishA,
            const int nMissiles);
    void spawnGodTimedMissiles(
            const eCharacterActionType at,
            const eTexPtr tex,
            eTile* const target,
            const eGodSound sound,
            const eFunc& finishA,
            const int time);

    void fightGod(eGod* const g, const eFunc& finishAttackA);

    void goToTarget();

    eGodType type() const { return mType; }

    void pauseAction();
    void resumeAction();
private:
    void hermesRun(const bool appear);

    void playAppearSound();
    void playDisappearSound();

    const eGodType mType;

    std::vector<ePausedAction> mPausedActions;
};

#endif // EGODACTION_H
