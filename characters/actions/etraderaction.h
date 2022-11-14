#ifndef ETRADERACTION_H
#define ETRADERACTION_H

#include "eactionwithcomeback.h"
#include "buildings/etradepost.h"
#include "ewalkablehelpers.h"

class eTraderAction : public eActionWithComeback {
public:
    using eActionWithComeback::eActionWithComeback;

    bool decide();

    void setTradePost(eTradePost* const tp);
    void setUnpackBuilding(eBuilding* const b);

    void setWalkable(const eWalkable& w);
private:
    void goToTradePost();
    void trade();
    void tradeIncrement();

    eWalkable mWalkable = eWalkableObject::sCreateDefault();

    int mCash = 1000;
    int mItems = 1000;
    stdptr<eTradePost> mTradePost;
    stdptr<eBuilding> mUnpackBuilding;
    bool mAtTradePost = false;
    bool mFinishedTrade = false;
    bool mNotFound = false;
};

#endif // ETRADERACTION_H
