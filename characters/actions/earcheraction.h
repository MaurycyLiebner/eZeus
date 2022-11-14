#ifndef EARCHERACTION_H
#define EARCHERACTION_H

#include "ecomplexaction.h"
#include "pointers/estdpointer.h"

class eArcherAction : public eComplexAction {
public:
    eArcherAction(eCharacter* const c);

    void increment(const int by);
    bool decide();

    void read(eReadStream& src);
    void write(eWriteStream& dst) const;
private:
    int mMissile = 0;
    int mRangeAttack = 0;
    int mAttackTime = 0;
    bool mAttack = false;
    stdptr<eCharacter> mAttackTarget;
};

class eAA_patrolFail : public eCharActFunc {
public:
    eAA_patrolFail(eGameBoard& board) :
        eCharActFunc(board, eCharActFuncType::AA_patrolFail) {}
    eAA_patrolFail(eGameBoard& board,
                   eArcherAction* const t) :
        eCharActFunc(board, eCharActFuncType::AA_patrolFail),
        mTptr(t) {}

    void call() override {
        if(!mTptr) return;
        const auto t = mTptr.get();
        t->setState(eCharacterActionState::failed);
    }

    void read(eReadStream& src) override {
        src.readCharacterAction(&board(), [this](eCharacterAction* const ca) {
            mTptr = static_cast<eArcherAction*>(ca);
        });
    }

    void write(eWriteStream& dst) const override {
        dst.writeCharacterAction(mTptr);
    }
private:
    stdptr<eArcherAction> mTptr;
};

class eAA_patrolFinish : public eCharActFunc {
public:
    eAA_patrolFinish(eGameBoard& board) :
        eCharActFunc(board, eCharActFuncType::AA_patrolFinish) {}
    eAA_patrolFinish(eGameBoard& board, eArcherAction* const t) :
        eCharActFunc(board, eCharActFuncType::AA_patrolFinish),
        mTptr(t) {}

    void call() override {
        if(!mTptr) return;
        const auto t = mTptr.get();
        t->setState(eCharacterActionState::finished);
    }

    void read(eReadStream& src) override {
        src.readCharacterAction(&board(), [this](eCharacterAction* const ca) {
            mTptr = static_cast<eArcherAction*>(ca);
        });
    }

    void write(eWriteStream& dst) const override {
        dst.writeCharacterAction(mTptr);
    }
private:
    stdptr<eArcherAction> mTptr;
};

#endif // EARCHERACTION_H
