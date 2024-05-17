#ifndef ESOLDIERACTION_H
#define ESOLDIERACTION_H

#include "ecomplexaction.h"

#include <map>

#include "characters/echaracter.h"
#include "walkable/eobsticlehandler.h"
#include "buildings/ebuilding.h"

class eSoldier;

class eAttackTarget {
public:
    eAttackTarget();
    eAttackTarget(eCharacter* const c);
    eAttackTarget(eBuilding* const b);

    eTile* tile() const;
    bool valid() const;
    bool defend(const double a);
    bool dead() const;
    void clear();

    bool building() const;

    double absX() const;
    double absY() const;

    void read(eGameBoard& board, eReadStream& src) {
        src.readCharacter(&board, [this](eCharacter* const c) {
            mC = c;
        });
        src.readBuilding(&board, [this](eBuilding* const b) {
            mB = b;
        });
    }

    void write(eWriteStream& dst) const {
        dst.writeCharacter(mC);
        dst.writeBuilding(mB);
    }
private:
    stdptr<eCharacter> mC;
    stdptr<eBuilding> mB;
};

class eSoldierAction : public eComplexAction {
    friend class eSoldierObsticleHandler;
public:
    eSoldierAction(eCharacter* const c);

    bool decide() override;

    void increment(const int by) override;

    void read(eReadStream& src) override;
    void write(eWriteStream& dst) const override;

    void moveBy(const double dx, const double dy);

    using eAction = std::function<void()>;
    void goTo(const int fx, const int fy,
              const int dist = 0,
              const eAction& findFailAct = nullptr,
              const eAction& findFinishAct = nullptr);
    void goHome();
    void goAbroad();
    void goBackToBanner(const eAction& findFailAct = nullptr,
                        const eAction& findFinishAct = nullptr);

    void beingAttacked(eSoldier* const ss);
    void beingAttacked(const int ttx, const int tty);

    static eBuilding* sFindHome(const eCharacterType t,
                                const eGameBoard& brd);
private:
    bool attackBuilding(eTile* const t);
    stdsptr<eObsticleHandler> obsticleHandler();

    int mGoToBannerCountdown = 0;
    double mAngle{0.};

    int mMissile = 0;

    int mRangeAttack = 0;
    int mBuildingAttack = 0;

    int mLookForEnemy = 0;
    int mAttackTime = 0;
    bool mAttack = false;
    eAttackTarget mAttackTarget;
};

class eSoldierObsticleHandler : public eObsticleHandler {
public:
    eSoldierObsticleHandler(eGameBoard& board) :
        eObsticleHandler(board, eObsticleHandlerType::soldier) {}
    eSoldierObsticleHandler(eGameBoard& board,
                            eSoldierAction* const t) :
        eObsticleHandler(board, eObsticleHandlerType::soldier),
        mTptr(t) {}

    bool handle(eTile* const tile) override {
        if(!mTptr) return false;
        const auto ub = tile->underBuilding();
        if(!ub) return false;
        const auto ubt = ub->type();
        const bool r = eBuilding::sWalkableBuilding(ubt);
        if(r) return false;
        mTptr->attackBuilding(tile);
        return true;
    }

    void read(eReadStream& src) override {
        src.readCharacterAction(&board(), [this](eCharacterAction* const ca) {
            mTptr = static_cast<eSoldierAction*>(ca);
        });
    }

    void write(eWriteStream& dst) const override {
        dst.writeCharacterAction(mTptr);
    }
private:
    stdptr<eSoldierAction> mTptr;
};

class eSA_goToFinish : public eCharActFunc {
public:
    eSA_goToFinish(eGameBoard& board) :
        eCharActFunc(board, eCharActFuncType::SA_goToFinish) {}
    eSA_goToFinish(eGameBoard& board, eCharacter* const c) :
        eCharActFunc(board, eCharActFuncType::SA_goToFinish),
        mCptr(c) {}

    void call() override {
        if(!mCptr) return;
        mCptr->setActionType(eCharacterActionType::stand);
    }

    void read(eReadStream& src) override {
        src.readCharacter(&board(), [this](eCharacter* const c) {
            mCptr = c;
        });
    }

    void write(eWriteStream& dst) const override {
        dst.writeCharacter(mCptr);
    }
private:
    stdptr<eCharacter> mCptr;
};

class eSA_goHomeFinish : public eCharActFunc {
public:
    eSA_goHomeFinish(eGameBoard& board) :
        eCharActFunc(board, eCharActFuncType::SA_goHomeFinish) {}
    eSA_goHomeFinish(eGameBoard& board, eCharacter* const c) :
        eCharActFunc(board, eCharActFuncType::SA_goHomeFinish),
        mCptr(c) {}

    void call() override {
        if(!mCptr) return;
        mCptr->kill();
    }

    void read(eReadStream& src) override {
        src.readCharacter(&board(), [this](eCharacter* const c) {
            mCptr = c;
        });
    }

    void write(eWriteStream& dst) const override {
        dst.writeCharacter(mCptr);
    }
private:
    stdptr<eCharacter> mCptr;
};

#endif // ESOLDIERACTION_H
