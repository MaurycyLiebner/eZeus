#ifndef EGODACTION_H
#define EGODACTION_H

#include "egodmonsteraction.h"

#include "characters/gods/egod.h"

class eDestructionTextures;
enum class eGodSound;

class eGodAction : public eGodMonsterAction {
public:
    eGodAction(eCharacter* const c,
               const eAction& failAction,
               const eAction& finishAction);

    using eFunc = std::function<void()>;
    void appear(const eFunc& finish = nullptr);
    void disappear(const bool die = false,
                   const eFunc& finish = nullptr);
    void teleport(eTile* const tile);

    void patrol(const eAction& finishAct = [](){},
                const int dist = 100);

    void randomPlaceOnBoard();

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

    bool lookForSoldierAttack(const int dtime, int& time,
                              const int freq, const int range);

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
private:
    void hermesRun(const bool appear);

    void playAppearSound();
    void playDisappearSound();

    const eGodType mType;
};

#endif // EGODACTION_H
