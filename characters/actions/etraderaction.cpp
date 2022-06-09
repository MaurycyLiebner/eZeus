#include "etraderaction.h"

#include "emovetoaction.h"

bool eTraderAction::decide() {
    const auto c = character();

    const auto a = e::make_shared<eMoveToAction>(
                       c, [](){}, [](){});
    a->setRemoveLastTurn(true);
    const auto tp = mTradePost;
    a->setFindFailAction([tp]() {
        if(!tp) return;
        tp->updateRouteStart();
    });
    a->start(mTradePost);
    setCurrentAction(a);
    c->setActionType(eCharacterActionType::walk);
    return true;
}

void eTraderAction::setTradePost(eTradePost* const tp) {
    mTradePost = tp;
}
