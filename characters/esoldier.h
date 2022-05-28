#ifndef ESOLDIER_H
#define ESOLDIER_H

#include "echaracter.h"

class eSoldierAction;

class eSoldier : public eCharacter {
public:
    using eCharacter::eCharacter;

    bool selected() const { return mSelected; }
    void setSelected(const bool s) { mSelected = s; }

    eSoldierAction* soldierAction() const;
    void setSoldierAction(const stdsptr<eSoldierAction>& a);
private:
    stdsptr<eSoldierAction> mAction;
    bool mSelected = false;
};

#endif // ESOLDIER_H
