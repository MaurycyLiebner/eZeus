#include "etraderaction.h"

#include "emovetoaction.h"
#include "ewaitaction.h"

eTraderAction::eTraderAction(eCharacter* const c) :
    eActionWithComeback(c, eCharActionType::traderAction) {}

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

void eTraderAction::read(eReadStream& src) {
    eActionWithComeback::read(src);
    mWalkable = src.readWalkable();
    src >> mCash;
    src >> mItems;
    src.readBuilding(&board(), [this](eBuilding* const b) {
        mTradePost = static_cast<eTradePost*>(b);
    });
    src.readBuilding(&board(), [this](eBuilding* const b) {
        mUnpackBuilding = b;
    });
    src >> mAtTradePost;
    src >> mFinishedTrade;
    src >> mNotFound;
}

void eTraderAction::write(eWriteStream& dst) const {
    eActionWithComeback::write(dst);
    dst.writeWalkable(mWalkable.get());
    dst << mCash;
    dst << mItems;
    dst.writeBuilding(mTradePost);
    dst.writeBuilding(mUnpackBuilding);
    dst << mAtTradePost;
    dst << mFinishedTrade;
    dst << mNotFound;
}

void eTraderAction::setTradePost(eTradePost* const tp) {
    mTradePost = tp;
}

void eTraderAction::setUnpackBuilding(eBuilding* const b) {
    mUnpackBuilding = b;
}

void eTraderAction::setWalkable(const stdsptr<eWalkableObject>& w) {
    mWalkable = w;
}

void eTraderAction::goToTradePost() {
    const auto c = character();

    const stdptr<eTraderAction> tptr(this);
    const auto fail = std::make_shared<eTA_tradeFail>(
                          board(), this);
    stdptr<eCharacter> cptr(c);
    const auto tp = mTradePost;
    const auto finish = std::make_shared<eTA_goToTradePostFinish>(
                            board(), this);

    const auto a = e::make_shared<eMoveToAction>(c);
    a->setFailAction(fail);
    a->setFinishAction(finish);
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
    const auto fail = std::make_shared<eTA_tradeFail>(
                          board(), this);
    const auto finish = std::make_shared<eTA_tradeFinish>(
                            board(), this);
    const auto a = e::make_shared<eWaitAction>(c);
    a->setFailAction(fail);
    a->setFinishAction(finish);
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
