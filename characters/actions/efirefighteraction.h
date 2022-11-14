#ifndef EFIREFIGHTERACTION_H
#define EFIREFIGHTERACTION_H

#include "epatrolaction.h"

#include "engine/etile.h"

class eFireFighterAction : public ePatrolAction {
    friend class eFFA_lookForFireFail;
public:
    eFireFighterAction(eCharacter* const c);

    bool decide() override;
    void increment(const int by) override;

    void read(eReadStream& src) override;
    void write(eWriteStream& dst) const override;
private:
    bool lookForFire();
    void putOutFire(eTile* const tile);

    bool mFireFighting{false};
    int mFireCheck{0};

    int mUsedWater = 0;
};

class eFFA_lookForFireFail : public eCharActFunc {
public:
    eFFA_lookForFireFail(eGameBoard& board) :
        eCharActFunc(board, eCharActFuncType::FFA_lookForFireFail) {}
    eFFA_lookForFireFail(eGameBoard& board,
                         eFireFighterAction* const ca) :
        eCharActFunc(board, eCharActFuncType::FFA_lookForFireFail),
        mPtr(ca) {}

    void call() override {
        if(!mPtr) return;
        const auto t = mPtr.get();
        if(!t->mFireFighting) return;
        t->mFireFighting = false;
        const auto c = t->character();
        c->setActionType(eCharacterActionType::walk);
        t->goBackDecision(eWalkableObject::sCreateDefault());
    }

    void read(eReadStream& src) override {
        src.readCharacterAction(&board(), [this](eCharacterAction* const ca) {
            mPtr = static_cast<eFireFighterAction*>(ca);
        });
    }

    void write(eWriteStream& dst) const override {
        dst.writeCharacterAction(mPtr);
    }
private:
    stdptr<eFireFighterAction> mPtr;
};

class eFFA_putOutFireFinish : public eCharActFunc {
public:
    eFFA_putOutFireFinish(eGameBoard& board) :
        eCharActFunc(board, eCharActFuncType::FFA_putOutFireFinish) {}
    eFFA_putOutFireFinish(eGameBoard& board, eCharacter* const c,
                          eTile* const t) :
        eCharActFunc(board, eCharActFuncType::FFA_putOutFireFinish),
        mCptr(c), mTile(t) {}

    void call() override {
        if(!mCptr) return;
        mCptr->setActionType(eCharacterActionType::stand);
        if(const auto b = mTile->underBuilding()) {
            b->setOnFire(false);
        }
    }

    void read(eReadStream& src) override {
        src.readCharacter(&board(), [this](eCharacter* const c) {
            mCptr = c;
        });
        mTile = src.readTile(board());
    }

    void write(eWriteStream& dst) const override {
        dst.writeCharacter(mCptr);
        dst.writeTile(mTile);
    }
private:
    stdptr<eCharacter> mCptr;
    eTile* mTile = nullptr;
};

#endif // EFIREFIGHTERACTION_H
