#include "esoldier.h"

eSoldierAction* eSoldier::soldierAction() const {
    return mAction.get();
}

void eSoldier::setSoldierAction(const stdsptr<eSoldierAction>& a) {
    mAction = a;
}
