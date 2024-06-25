#ifndef EMONSTERACTION_H
#define EMONSTERACTION_H

#include "egodmonsteraction.h"

#include "characters/monsters/emonster.h"
#include "audio/esounds.h"
#include "characters/actions/walkable/eobsticlehandler.h"

enum class eMonsterAttackStage {
    none, wait, goTo, patrol, goBack
};

class eMonsterAction : public eGodMonsterAction {
    friend class eMonsterObsticleHandler;
public:
    eMonsterAction(eCharacter* const c);

    void increment(const int by) override;
    bool decide() override;

    void read(eReadStream& src) override;
    void write(eWriteStream& dst) const override;

    eMonsterAttackStage stage() const { return mStage; }

    void goToTarget();
    void goBack();
    void monsterPatrol();
private:
    void destroyBuilding(eBuilding* const b);
    eTile* closestEmptySpace(const int rdx, const int rdy) const;
    void randomPlaceOnBoard();
    stdsptr<eObsticleHandler> obsticleHandler();
    bool lookForAttack(const int dtime, int& time,
                       const int freq, const int range);
    bool lookForRangeAction(const int dtime,
                            int& time, const int freq,
                            const int range,
                            const eCharacterActionType at,
                            const stdsptr<eGodAct>& act,
                            const stdsptr<eCharActFunc>& missileSound);

    eTile* mHomeTile = nullptr;
    eMonsterAttackStage mStage{eMonsterAttackStage::none};
    const eMonsterType mType;
    int mLookForAttack = 0;
};

class eGoToTargetTryAgain : public eFindFailFunc {
public:
    eGoToTargetTryAgain(eGameBoard& board) :
        eFindFailFunc(board, eFindFailFuncType::tryAgain) {}
    eGoToTargetTryAgain(eGameBoard& board, eMonsterAction* const ca) :
        eFindFailFunc(board, eFindFailFuncType::tryAgain),
        mTptr(ca) {}

    void call(eTile* const tile) {
        (void)tile;
        if(!mTptr) return;
        mTptr->setCurrentAction(nullptr);
    }

    void read(eReadStream& src) {
        src.readCharacterAction(&board(), [this](eCharacterAction* const ca) {
            mTptr = static_cast<eMonsterAction*>(ca);
        });
    }

    void write(eWriteStream& dst) const {
        dst.writeCharacterAction(mTptr);
    }
private:
    stdptr<eMonsterAction> mTptr;
};

class eMA_destroyBuildingFinish : public eCharActFunc {
public:
    eMA_destroyBuildingFinish(eGameBoard& board) :
        eCharActFunc(board, eCharActFuncType::MA_destroyBuildingFinish) {}
    eMA_destroyBuildingFinish(eGameBoard& board, eMonsterAction* const ca,
                              eBuilding* const b) :
        eCharActFunc(board, eCharActFuncType::MA_destroyBuildingFinish),
        mTptr(ca), mBptr(b) {}

    void call() override {
        if(!mTptr) return;
        mTptr->resumeAction();
        if(!mBptr) return;
        mBptr->collapse();
        eSounds::playCollapseSound();
    }

    void read(eReadStream& src) override {
        src.readCharacterAction(&board(), [this](eCharacterAction* const ca) {
            mTptr = static_cast<eMonsterAction*>(ca);
        });
        src.readBuilding(&board(), [this](eBuilding* const b) {
            mBptr = b;
        });
    }

    void write(eWriteStream& dst) const override {
        dst.writeCharacterAction(mTptr);
        dst.writeBuilding(mBptr);
    }
private:
    stdptr<eMonsterAction> mTptr;
    stdptr<eBuilding> mBptr;
};

class eMA_lookForRangeActionFinishAttack : public eCharActFunc {
public:
    eMA_lookForRangeActionFinishAttack(eGameBoard& board) :
        eCharActFunc(board, eCharActFuncType::MA_lookForRangeActionFinishAttack) {}
    eMA_lookForRangeActionFinishAttack(eGameBoard& board, eMonsterAction* const ca) :
        eCharActFunc(board, eCharActFuncType::MA_lookForRangeActionFinishAttack),
        mTptr(ca) {}

    void call() override {
        if(!mTptr) return;
        mTptr->resumeAction();
    }

    void read(eReadStream& src) override {
        src.readCharacterAction(&board(), [this](eCharacterAction* const ca) {
            mTptr = static_cast<eMonsterAction*>(ca);
        });
    }

    void write(eWriteStream& dst) const override {
        dst.writeCharacterAction(mTptr);
    }
private:
    stdptr<eMonsterAction> mTptr;
};

class eMonsterObsticleHandler : public eObsticleHandler {
public:
    eMonsterObsticleHandler(eGameBoard& board) :
        eObsticleHandler(board, eObsticleHandlerType::monster) {}
    eMonsterObsticleHandler(eGameBoard& board,
                            eMonsterAction* const t) :
        eObsticleHandler(board, eObsticleHandlerType::monster),
        mTptr(t) {}

    bool handle(eTile* const tile) override {
        if(!mTptr) return false;
        const auto ub = tile->underBuilding();
        if(!ub) return false;
        const auto ubt = ub->type();
        const bool r = eBuilding::sWalkableBuilding(ubt);
        if(r) return false;
        mTptr->destroyBuilding(ub);
        return true;
    }

    void read(eReadStream& src) override {
        src.readCharacterAction(&board(), [this](eCharacterAction* const ca) {
            mTptr = static_cast<eMonsterAction*>(ca);
        });
    }

    void write(eWriteStream& dst) const override {
        dst.writeCharacterAction(mTptr);
    }
private:
    stdptr<eMonsterAction> mTptr;
};

#endif // EMONSTERACTION_H
