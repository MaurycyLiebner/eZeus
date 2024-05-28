#ifndef EDEFENDCITYACTION_H
#define EDEFENDCITYACTION_H

#include "egodmonsteraction.h"

enum class eDefendCityStage {
    none, appear, goTo, fight, comeback, disappear
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
    void goTo(const int fx, const int fy, const int dist);
    int range() const;

    eDefendCityStage mStage{eDefendCityStage::none};
    eTile* mStartTile = nullptr;
    stdptr<eCharacter> mAttackTarget;
    bool mAttack = false;
    int mLookForEnemy = 0;
    int mAttackTime = 0;
    int mRangeAttack = 0;
    double mAngle{0.};
    int mMissile = 0;
};

#endif // EDEFENDCITYACTION_H
