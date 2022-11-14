#ifndef EGODACTION_H
#define EGODACTION_H

#include "egodmonsteraction.h"

#include "characters/gods/egod.h"
#include "etilehelper.h"
#include "emovetoaction.h"

class eDestructionTextures;
enum class eGodSound;

class eGodAction : public eGodMonsterAction {
public:
    eGodAction(eCharacter* const c);

    using eFunc = std::function<void()>;
    void appear(const eFunc& finish = nullptr);
    void disappear(const bool die = false,
                   const stdsptr<eCharActFunc>& finish = nullptr);
    void teleport(eTile* const tile);

    void patrol(const stdsptr<eCharActFunc>& finishAct = nullptr,
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
                            const stdsptr<eCharActFunc>& finishMissileA);
    bool lookForBlessCurse(const int dtime, int& time,
                           const int freq, const int range,
                           const double bless);

    bool lookForSoldierAttack(const int dtime, int& time,
                              const int freq, const int range);

    void spawnGodMissile(const eCharacterActionType at,
                         const eTexPtr tex,
                         eTile* const target,
                         const eGodSound sound,
                         const stdsptr<eCharActFunc>& finishMissileA,
                         const stdsptr<eCharActFunc>& finishAttackA = nullptr);
    void spawnGodMultipleMissiles(const eCharacterActionType at,
            const eTexPtr tex,
            eTile* const target,
            const eGodSound sound,
            const stdsptr<eCharActFunc>& playHitSound,
            const stdsptr<eCharActFunc>& finishA,
            const int nMissiles);
    void spawnGodTimedMissiles(const eCharacterActionType at,
            const eTexPtr tex,
            eTile* const target,
            const eGodSound sound,
            const stdsptr<eCharActFunc>& playHitSound,
            const stdsptr<eCharActFunc>& finishA,
            const int time);

    void fightGod(eGod* const g, const stdsptr<eCharActFunc>& finishAttackA);

    void goToTarget();

    eGodType type() const { return mType; }

    void playAppearSound();
    void playDisappearSound();
private:
    void hermesRun(const bool appear);

    const eGodType mType;
};

class eGA_patrolFailFail : public eCharActFunc {
public:
    eGA_patrolFailFail(eGameBoard& board) :
        eCharActFunc(board, eCharActFuncType::GA_patrolFailFail) {}
    eGA_patrolFailFail(eGameBoard& board, eGodAction* const ca,
                       const stdsptr<eCharActFunc>& finishAct) :
        eCharActFunc(board, eCharActFuncType::GA_patrolFailFail),
        mTptr(ca), mFinishAct(finishAct) {}

    void call() override {
        if(!mTptr) return;
        const auto t = mTptr.get();
        t->moveAround(mFinishAct, 15000);
    }

    void read(eReadStream& src) override {
        src.readCharacterAction(&board(), [this](eCharacterAction* const ca) {
            mTptr = static_cast<eGodAction*>(ca);
        });
        {
            bool hasFinish;
            src >> hasFinish;
            if(hasFinish) {
                eCharActFuncType type;
                src >> type;
                const auto f = eCharActFunc::sCreate(board(), type);
                f->read(src);
                mFinishAct = f;
            }
        }
    }

    void write(eWriteStream& dst) const override {
        dst.writeCharacterAction(mTptr);
        {
            const bool hasFinish = mFinishAct != nullptr;
            dst << hasFinish;
            if(hasFinish) {
                dst << mFinishAct->type();
                mFinishAct->write(dst);
            }
        }
    }
private:
    stdptr<eGodAction> mTptr;
    stdsptr<eCharActFunc> mFinishAct;
};

class eGA_patrolFailFinish : public eCharActFunc {
public:
    eGA_patrolFailFinish(eGameBoard& board) :
        eCharActFunc(board, eCharActFuncType::GA_patrolFailFinish) {}
    eGA_patrolFailFinish(eGameBoard& board, eGodAction* const ca,
                         const stdsptr<eCharActFunc>& finishAct,
                         const int dist) :
        eCharActFunc(board, eCharActFuncType::GA_patrolFailFinish),
        mTptr(ca), mFinishAct(finishAct), mDist(dist) {}

    void call() override {
        if(!mTptr) return;
        const auto t = mTptr.get();
        t->patrol(mFinishAct, mDist);
    }

    void read(eReadStream& src) override {
        src.readCharacterAction(&board(), [this](eCharacterAction* const ca) {
            mTptr = static_cast<eGodAction*>(ca);
        });
        {
            bool hasFinish;
            src >> hasFinish;
            if(hasFinish) {
                eCharActFuncType type;
                src >> type;
                const auto f = eCharActFunc::sCreate(board(), type);
                f->read(src);
                mFinishAct = f;
            }
        }
        src >> mDist;
    }

    void write(eWriteStream& dst) const override {
        dst.writeCharacterAction(mTptr);
        {
            const bool hasFinish = mFinishAct != nullptr;
            dst << hasFinish;
            if(hasFinish) {
                dst << mFinishAct->type();
                mFinishAct->write(dst);
            }
        }
        dst << mDist;
    }
private:
    stdptr<eGodAction> mTptr;
    stdsptr<eCharActFunc> mFinishAct;
    int mDist = 100;
};

class eGA_patrolFail : public eCharActFunc {
public:
    eGA_patrolFail(eGameBoard& board) :
        eCharActFunc(board, eCharActFuncType::GA_patrolFail) {}
    eGA_patrolFail(eGameBoard& board, eGodAction* const ca,
                   eCharacter* const c,
                   const stdsptr<eCharActFunc>& finishAct,
                   const int dist) :
        eCharActFunc(board, eCharActFuncType::GA_patrolFail),
        mTptr(ca), mCptr(c), mFinishAct(finishAct), mDist(dist) {}

    void call() override {
        if(!mTptr || !mCptr) return;
        const auto c = mCptr.get();
        const auto t = c->tile();
        const auto cr = eTileHelper::closestRoad(t->x(), t->y(), board());
        if(cr) {
            const auto fail = std::make_shared<eGA_patrolFailFail>(
                                  board(), mTptr.get(), mFinishAct);
            const auto finish = std::make_shared<eGA_patrolFailFinish>(
                                    board(), mTptr.get(), mFinishAct, mDist);
            const auto a = e::make_shared<eMoveToAction>(c);
            a->setFailAction(fail);
            a->setFinishAction(finish);
            a->setFindFailAction([fail]() {
                fail->call();
            });
            a->start(cr);
            mTptr->setCurrentAction(a);
        } else {
            mTptr->moveAround(mFinishAct, 15000);
        }
    }

    void read(eReadStream& src) override {
        src.readCharacterAction(&board(), [this](eCharacterAction* const ca) {
            mTptr = static_cast<eGodAction*>(ca);
        });
        src.readCharacter(&board(), [this](eCharacter* const c) {
            mCptr = c;
        });
        {
            bool hasFinish;
            src >> hasFinish;
            if(hasFinish) {
                eCharActFuncType type;
                src >> type;
                const auto f = eCharActFunc::sCreate(board(), type);
                f->read(src);
                mFinishAct = f;
            }
        }
        src >> mDist;
    }

    void write(eWriteStream& dst) const override {
        dst.writeCharacterAction(mTptr);
        dst.writeCharacter(mCptr);
        {
            const bool hasFinish = mFinishAct != nullptr;
            dst << hasFinish;
            if(hasFinish) {
                dst << mFinishAct->type();
                mFinishAct->write(dst);
            }
        }
        dst << mDist;
    }
private:
    stdptr<eGodAction> mTptr;
    stdptr<eCharacter> mCptr;
    stdsptr<eCharActFunc> mFinishAct;
    int mDist = 100;
};

class eGA_lookForSoldierAttackFinish : public eCharActFunc {
public:
    eGA_lookForSoldierAttackFinish(eGameBoard& board) :
        eCharActFunc(board, eCharActFuncType::GA_lookForSoldierAttackFinish) {}
    eGA_lookForSoldierAttackFinish(eGameBoard& board, eGodAction* const ca,
                                   eTile* const tile) :
        eCharActFunc(board, eCharActFuncType::GA_lookForSoldierAttackFinish),
        mTptr(ca), mTile(tile) {}

    void call() override {
        if(!mTptr) return;
        const auto t = mTptr.get();
        const auto c = t->character();
        c->changeTile(mTile);
        t->appear();
    }

    void read(eReadStream& src) override {
        src.readCharacterAction(&board(), [this](eCharacterAction* const ca) {
            mTptr = static_cast<eGodAction*>(ca);
        });
        mTile = src.readTile(board());
    }

    void write(eWriteStream& dst) const override {
        dst.writeCharacterAction(mTptr);
        dst.writeTile(mTile);
    }
private:
    stdptr<eGodAction> mTptr;
    eTile* mTile = nullptr;
};

class eGA_teleportFinish : public eCharActFunc {
public:
    eGA_teleportFinish(eGameBoard& board) :
        eCharActFunc(board, eCharActFuncType::GA_teleportFinish) {}
    eGA_teleportFinish(eGameBoard& board, eGodAction* const ca,
                       eTile* const tile) :
        eCharActFunc(board, eCharActFuncType::GA_teleportFinish),
        mTptr(ca), mTile(tile) {}

    void call() override {
        if(!mTptr) return;
        const auto t = mTptr.get();
        const auto c = t->character();
        c->changeTile(mTile);
        t->appear();
    }

    void read(eReadStream& src) override {
        src.readCharacterAction(&board(), [this](eCharacterAction* const ca) {
            mTptr = static_cast<eGodAction*>(ca);
        });
        mTile = src.readTile(board());
    }

    void write(eWriteStream& dst) const override {
        dst.writeCharacterAction(mTptr);
        dst.writeTile(mTile);
    }
private:
    stdptr<eGodAction> mTptr;
    eTile* mTile = nullptr;
};

class eGA_hermesRunFinish : public eCharActFunc {
public:
    eGA_hermesRunFinish(eGameBoard& board) :
        eCharActFunc(board, eCharActFuncType::GA_hermesRunFinish) {}
    eGA_hermesRunFinish(eGameBoard& board, eGodAction* const ca,
                        eCharacter* const c, const bool appear) :
        eCharActFunc(board, eCharActFuncType::GA_hermesRunFinish),
        mTptr(ca), mCptr(c), mAppear(appear) {}

    void call() override {
        if(!mTptr || !mCptr) return;
        const auto t = mTptr.get();
        mCptr->setSpeed(1.);
        if(!mAppear) t->playDisappearSound();
    }

    void read(eReadStream& src) override {
        src.readCharacterAction(&board(), [this](eCharacterAction* const ca) {
            mTptr = static_cast<eGodAction*>(ca);
        });
        src.readCharacter(&board(), [this](eCharacter* const c) {
            mCptr = c;
        });

        src >> mAppear;
    }

    void write(eWriteStream& dst) const override {
        dst.writeCharacterAction(mTptr);
        dst.writeCharacter(mCptr);

        dst << mAppear;
    }
private:
    stdptr<eGodAction> mTptr;
    stdptr<eCharacter> mCptr;
    bool mAppear;
};

#endif // EGODACTION_H
