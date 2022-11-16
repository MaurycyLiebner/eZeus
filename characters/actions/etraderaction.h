#ifndef ETRADERACTION_H
#define ETRADERACTION_H

#include "eactionwithcomeback.h"
#include "buildings/etradepost.h"
#include "ewalkablehelpers.h"

class eTraderAction : public eActionWithComeback {
    friend class eTA_tradeFail;
    friend class eTA_tradeFinish;
    friend class eTA_goToTradePostFinish;
public:
    eTraderAction(eCharacter* const c);

    bool decide() override;

    void read(eReadStream& src) override;
    void write(eWriteStream& dst) const override;

    void setTradePost(eTradePost* const tp);
    void setUnpackBuilding(eBuilding* const b);

    void setWalkable(const stdsptr<eWalkableObject>& w);
private:
    void goToTradePost();
    void trade();
    void tradeIncrement();

    stdsptr<eWalkableObject> mWalkable =
            eWalkableObject::sCreateDefault();

    int mCash = 1000;
    int mItems = 1000;
    stdptr<eTradePost> mTradePost;
    stdptr<eBuilding> mUnpackBuilding;
    bool mAtTradePost = false;
    bool mFinishedTrade = false;
    bool mNotFound = false;
};

class eTA_tradeFail : public eCharActFunc {
public:
    eTA_tradeFail(eGameBoard& board) :
        eCharActFunc(board, eCharActFuncType::TA_tradeFail) {}
    eTA_tradeFail(eGameBoard& board, eTraderAction* const t) :
        eCharActFunc(board, eCharActFuncType::TA_tradeFail),
        mTptr(t) {}

    void call() override {
        if(!mTptr) return;
        const auto t = mTptr.get();
        t->goBack(t->mWalkable);
    }

    void read(eReadStream& src) override {
        src.readCharacterAction(&board(), [this](eCharacterAction* const ca) {
            mTptr = static_cast<eTraderAction*>(ca);
        });
    }

    void write(eWriteStream& dst) const override {
        dst.writeCharacterAction(mTptr);
    }
private:
    stdptr<eTraderAction> mTptr;
};

class eTA_tradeFinish : public eCharActFunc {
public:
    eTA_tradeFinish(eGameBoard& board) :
        eCharActFunc(board, eCharActFuncType::TA_tradeFinish) {}
    eTA_tradeFinish(eGameBoard& board, eTraderAction* const t) :
        eCharActFunc(board, eCharActFuncType::TA_tradeFinish),
        mTptr(t) {}

    void call() override {
        if(!mTptr) return;
        const auto t = mTptr.get();
        t->tradeIncrement();
    }

    void read(eReadStream& src) override {
        src.readCharacterAction(&board(), [this](eCharacterAction* const ca) {
            mTptr = static_cast<eTraderAction*>(ca);
        });
    }

    void write(eWriteStream& dst) const override {
        dst.writeCharacterAction(mTptr);
    }
private:
    stdptr<eTraderAction> mTptr;
};

class eTA_goToTradePostFinish : public eCharActFunc {
public:
    eTA_goToTradePostFinish(eGameBoard& board) :
        eCharActFunc(board, eCharActFuncType::TA_goToTradePostFinish) {}
    eTA_goToTradePostFinish(eGameBoard& board, eTraderAction* const t) :
        eCharActFunc(board, eCharActFuncType::TA_goToTradePostFinish),
        mTptr(t) {}

    void call() override {
        if(!mTptr) return;
        const auto t = mTptr.get();
        if(!t->mTradePost) return;
        t->mAtTradePost = true;
        const auto tt = t->mTradePost->tpType();
        if(tt == eTradePostType::pier) {
            const auto o = t->mTradePost->orientation();
            eOrientation oo;
            switch(o) {
            case eOrientation::bottomLeft:
            case eOrientation::topRight:
                oo = eOrientation::topLeft;
                break;
            default:
            case eOrientation::bottomRight:
            case eOrientation::topLeft:
                oo = eOrientation::topRight;
                break;
            }
            const auto c = t->character();
            c->setOrientation(oo);
        }
    }

    void read(eReadStream& src) override {
        src.readCharacterAction(&board(), [this](eCharacterAction* const ca) {
            mTptr = static_cast<eTraderAction*>(ca);
        });
    }

    void write(eWriteStream& dst) const override {
        dst.writeCharacterAction(mTptr);
    }
private:
    stdptr<eTraderAction> mTptr;
};

#endif // ETRADERACTION_H
