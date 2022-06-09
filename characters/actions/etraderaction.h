#ifndef ETRADERACTION_H
#define ETRADERACTION_H

#include "ecomplexaction.h"
#include "buildings/etradepost.h"

class eTraderAction : public eComplexAction {
public:
    using eComplexAction::eComplexAction;

    bool decide();

    void setTradePost(eTradePost* const tp);
private:
    stdptr<eTradePost> mTradePost = nullptr;
};

#endif // ETRADERACTION_H
