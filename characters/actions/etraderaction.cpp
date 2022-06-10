#include "etraderaction.h"

#include "emovetoaction.h"
#include "ewaitaction.h"

bool eTraderAction::decide() {
    const bool r = eActionWithComeback::decide();
    if(r) return r;

    if(mFinishedTrade || !mTradePost) {
        const auto c = character();
        c->setActionType(eCharacterActionType::walk);
        goBack(eWalkableHelpers::sDefaultWalkable);
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

void eTraderAction::goToTradePost() {
    const auto c = character();

    const stdptr<eTraderAction> tptr(this);
    const auto fail = [tptr, this]() {
        if(!tptr) return;
        goBack(eWalkableHelpers::sDefaultWalkable);
    };
    const auto finish = [tptr, this]() {
        if(!tptr) return;
        if(!mTradePost) return;
        mAtTradePost = true;
    };

    const auto a = e::make_shared<eMoveToAction>(
                       c, fail, finish);
    a->setRemoveLastTurn(true);
    const auto tp = mTradePost;
    a->setFindFailAction([tp]() {
        if(!tp) return;
        tp->updateRouteStart();
    });
    a->start(mTradePost);
    setCurrentAction(a);
    c->setActionType(eCharacterActionType::walk);
}

void eTraderAction::trade() {
    const auto c = character();

    const stdptr<eTraderAction> tptr(this);
    const auto fail = [tptr, this]() {
        if(!tptr) return;
        goBack(eWalkableHelpers::sDefaultWalkable);
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
