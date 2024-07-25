#ifndef EDEFENDCITYACTION_H
#define EDEFENDCITYACTION_H

#include "egodmonsteraction.h"

class eInvasionEvent;

enum class eDefendCityStage {
    none, appear, goTo, wait, fight, comeback, disappear
};

class eDefendCityAction : public eGodMonsterAction {
public:
    eDefendCityAction(eCharacter* const c);

    bool decide() override;
    void increment(const int by) override;

    void read(eReadStream& src) override;
    void write(eWriteStream& dst) const override;
private:
    void goToTarget();
    void goBack();
    bool goTo(const int fx, const int fy, const int dist);
    bool goToNearestSoldier();
    int range() const;

    stdptr<eInvasionEvent> mEvent;
    eDefendCityStage mStage{eDefendCityStage::none};
    eTile* mStartTile = nullptr;
    stdptr<eCharacter> mAttackTarget;
    bool mAttack = false;
    int mLookForEnemy = 0;
    int mAttackTime = 0;
    int mRangeAttack = 0;
    double mAngle{0.};
    int mMissile = 0;
    int mMaxKilled = 6;
    int mKilled = 0;
};

#endif // EDEFENDCITYACTION_H
