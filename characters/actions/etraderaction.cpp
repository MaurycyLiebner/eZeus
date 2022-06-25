#include "etraderaction.h"

#include "emovetoaction.h"
#include "ewaitaction.h"

bool eTraderAction::decide() {
    const bool r = eActionWithComeback::decide();
    if(r) return r;

    if(mFinishedTrade || !mTradePost || mNotFound) {
        const auto c = character();
        c->setActionType(eCharacterActionType::walk);
        goBack(mWalkable);
    } else if(mAtTradePost) {
        trade();
    } else {
        goToTradePost();
    }
    return true;
}

void eTraderAction::setTradePost(eTradePost* const tp) {
    mTradePost = tp;
}

void eTraderAction::setUnpackBuilding(eBuilding* const b) {
    mUnpackBuilding = b;
}

void eTraderAction::setWalkable(const eWalkable& w) {
    mWalkable = w;
}

void eTraderAction::goToTradePost() {
    const auto c = character();

    const stdptr<eTraderAction> tptr(this);
    const auto fail = [tptr, this]() {
        if(!tptr) return;
        goBack(mWalkable);
    };
    stdptr<eCharacter> cptr(c);
    const auto tp = mTradePost;
    const auto finish = [tptr, cptr, tp, this]() {
        if(!tptr) return;
        if(!mTradePost) return;
        mAtTradePost = true;
        if(!tp) return;
        const auto t = tp->tpType();
        if(cptr && t == eTradePostType::pier) {
            const auto o = tp->orientation();
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
            cptr->setOrientation(oo);
        }
    };

    const auto a = e::make_shared<eMoveToAction>(
                       c, fail, finish);
    a->setRemoveLastTurn(true);
    a->setFindFailAction([tp, tptr, cptr, this]() {
        if(!tp) return;
        tp->updateRouteStart();
        if(!tptr) return;
        mNotFound = true;
    });
    a->start(mUnpackBuilding, mWalkable);
    setCurrentAction(a);
    c->setActionType(eCharacterActionType::walk);
}

void eTraderAction::trade() {
    const auto c = character();

    const stdptr<eTraderAction> tptr(this);
    const auto fail = [tptr, this]() {
        if(!tptr) return;
        goBack(mWalkable);
    };
    const auto finish = [tptr, this]() {
        if(!tptr) return;
        tradeIncrement();
    };
    const auto a = e::make_shared<eWaitAction>(c, fail, finish);
    a->setTime(500);
    setCurrentAction(a);
    c->setActionType(eCharacterActionType::stand);
}

void eTraderAction::tradeIncrement() {
    if(!mTradePost) return;
    const int bought = mTradePost->buy(mCash);
    const int sold = mTradePost->sell(mItems);
    if(bought == 0 && sold == 0) {
        mFinishedTrade = true;
    } else {
        mCash -= bought;
        mItems -= sold;
    }
}
