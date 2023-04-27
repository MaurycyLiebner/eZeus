#ifndef EMONSTERATTACKEVENTWIDGET_H
#define EMONSTERATTACKEVENTWIDGET_H

#include "../ewidget.h"

#include "gameEvents/emonsterattackevent.h"

class eSwitchButton;

class eMonsterAttackEventWidget : public eWidget {
public:
    using eWidget::eWidget;

    void initialize(eMonsterAttackEvent* const e);
};

#endif // EMONSTERATTACKEVENTWIDGET_H
