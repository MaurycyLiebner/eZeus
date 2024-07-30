#ifndef EGODWORSHIPPEDACTION_H
#define EGODWORSHIPPEDACTION_H

#include "egodaction.h"

enum class eGodWorshippedStage {
    none, appear, goTo1, patrol1, goTo2, patrol2, disappear, defend,
    huntMonster, fightMonster
};

class eGodWorshippedAction : public eGodAction {
public:
    eGodWorshippedAction(eCharacter* const c);

    void increment(const int by) override;
    bool decide() override;

    void read(eReadStream& src) override;
    void write(eWriteStream& dst) const override;

    void lookForMonster();
private:
    void defendCity();
    void lookForMonsterFight();
    bool fightMonster(eMonster* const m);
    void huntMonster(eMonster* const m, const bool second);

    eGodWorshippedStage mStage{eGodWorshippedStage::none};

    int mLookForBless = 0;
    int mLookForSoldierAttack = 0;
    int mLookForCityDefense = 0;
    int mLookForMonster = 0;
};

class eGWA_huntMonsterFinish : public eCharActFunc {
public:
    eGWA_huntMonsterFinish(eGameBoard& board) :
        eCharActFunc(board, eCharActFuncType::GWA_huntMonsterFinish) {}
    eGWA_huntMonsterFinish(eGameBoard& board, eGodWorshippedAction* const ca) :
        eCharActFunc(board, eCharActFuncType::GWA_huntMonsterFinish),
        mTptr(ca) {}

    void call() {
        if(!mTptr) return;
        mTptr->lookForMonster();
    }

    void read(eReadStream& src) {
        src.readCharacterAction(&board(), [this](eCharacterAction* const ca) {
            mTptr = static_cast<eGodWorshippedAction*>(ca);
        });
    }

    void write(eWriteStream& dst) const {
        dst.writeCharacterAction(mTptr);
    }
private:
    stdptr<eGodWorshippedAction> mTptr;
};

#endif // EGODWORSHIPPEDACTION_H
