#ifndef ETRADERACTION_H
#define ETRADERACTION_H

#include "eactionwithcomeback.h"
#include "buildings/etradepost.h"

class eTraderAction : public eActionWithComeback {
public:
    using eActionWithComeback::eActionWithComeback;

    bool decide();

    void setTradePost(eTradePost* const tp);
private:
    void goToTradePost();
    void trade();
    void tradeIncrement();

    int mCash = 1000;
    int mItems = 1000;
    stdptr<eTradePost> mTradePost = nullptr;
    bool mAtTradePost = false;
    bool mFinishedTrade = false;
};

#endif // ETRADERACTION_H
