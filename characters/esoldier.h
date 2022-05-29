#ifndef ESOLDIER_H
#define ESOLDIER_H

#include "efightingpatroler.h"

class eSoldierAction;

class eSoldier : public eFightingPatroler {
public:
    using eFightingPatroler::eFightingPatroler;

    bool selected() const { return mSelected; }
    void setSelected(const bool s) { mSelected = s; }

    eSoldierAction* soldierAction() const;
    void setSoldierAction(const stdsptr<eSoldierAction>& a);
private:
    stdsptr<eSoldierAction> mAction;
    bool mSelected = false;
};

#endif // ESOLDIER_H
