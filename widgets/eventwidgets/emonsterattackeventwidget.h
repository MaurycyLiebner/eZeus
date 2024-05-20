#ifndef EMONSTERATTACKEVENTWIDGET_H
#define EMONSTERATTACKEVENTWIDGET_H

#include "../ewidget.h"

#include "gameEvents/emonsterinvasioneventbase.h"

class eSwitchButton;

class eMonsterAttackEventWidget : public eWidget {
public:
    using eWidget::eWidget;

    void initialize(eMonsterInvasionEventBase* const e);
};

#endif // EMONSTERATTACKEVENTWIDGET_H
