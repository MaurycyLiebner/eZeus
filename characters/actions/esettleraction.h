#ifndef ESETTLERACTION_H
#define ESETTLERACTION_H

#include "eactionwithcomeback.h"

class eSettlerAction : public eActionWithComeback {
    friend class eSA_findHouseFail;
    friend class eSA_findHouseFinish;
public:
    eSettlerAction(eCharacter* const c);

    bool decide() override;

    void read(eReadStream& src) override;
    void write(eWriteStream& dst) const override;

    void setNumberPeople(const int p);
    int nPeople() const { return mNPeople; }
protected:
    void findHouse();
    void goBack2();
    void leave();
    bool enterHouse();
private:
    int mNPeople = 8;
    bool mNoHouses = false;
};

class eSA_findHouseFail : public eCharActFunc {
public:
    eSA_findHouseFail(eGameBoard& board) :
        eCharActFunc(board, eCharActFuncType::SA_findHouseFail) {}
    eSA_findHouseFail(eGameBoard& board, eSettlerAction* const t) :
        eCharActFunc(board, eCharActFuncType::SA_findHouseFail),
        mTptr(t) {}

    void call() override {
        if(!mTptr) return;
        const auto t = mTptr.get();
        t->findHouse();
    }

    void read(eReadStream& src) override {
        src.readCharacterAction(&board(), [this](eCharacterAction* const ca) {
            mTptr = static_cast<eSettlerAction*>(ca);
        });
    }

    void write(eWriteStream& dst) const override {
        dst.writeCharacterAction(mTptr);
    }
private:
    stdptr<eSettlerAction> mTptr;
};

class eSA_findHouseFinish : public eCharActFunc {
public:
    eSA_findHouseFinish(eGameBoard& board) :
        eCharActFunc(board, eCharActFuncType::SA_findHouseFinish) {}
    eSA_findHouseFinish(eGameBoard& board, eSettlerAction* const t) :
        eCharActFunc(board, eCharActFuncType::SA_findHouseFinish),
        mTptr(t) {}

    void call() override {
        if(!mTptr) return;
        const auto t = mTptr.get();
        const bool r = t->enterHouse();
        const int nPeople = t->nPeople();
        if(r && nPeople <= 0) {
            t->setState(eCharacterActionState::finished);
        }
    }

    void read(eReadStream& src) override {
        src.readCharacterAction(&board(), [this](eCharacterAction* const ca) {
            mTptr = static_cast<eSettlerAction*>(ca);
        });
    }

    void write(eWriteStream& dst) const override {
        dst.writeCharacterAction(mTptr);
    }
private:
    stdptr<eSettlerAction> mTptr;
};

#endif // ESETTLERACTION_H
