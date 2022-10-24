#ifndef EGODACTION_H
#define EGODACTION_H

#include "ecomplexaction.h"

#include "characters/gods/egod.h"

class eDestructionTextures;
enum class eGodSound;

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

    void lookForBlessCurse(const int dtime,
                           int& time, const int freq,
                           const int range, const double bless);
    void blessCurse(eBuilding* const b, const double bb);
    using eTexPtr = eTextureCollection eDestructionTextures::*;
    void spawnGodMissile(const eCharacterActionType at,
                         const eTexPtr tex,
                         eTile* const target,
                         const eGodSound sound,
                         const eFunc& finishA);

    void goToTarget();

    eGodType type() const { return mType; }
private:
    void hermesRun(const bool appear);

    void playAppearSound();
    void playDisappearSound();

    void pauseAction();
    void resumeAction();

    const eGodType mType;

    stdsptr<eCharacterAction> mPausedAction;
    eOrientation mOrientation;
};

#endif // EGODACTION_H
