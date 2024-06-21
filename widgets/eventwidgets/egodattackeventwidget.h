#ifndef EGODATTACKEVENTWIDGET_H
#define EGODATTACKEVENTWIDGET_H

#include "../ewidget.h"

#include "gameEvents/egodattackevent.h"

class eSwitchButton;

class eGodAttackEventWidget : public eWidget {
public:
    using eWidget::eWidget;

    void initialize(eWidget* const parent,
                    eGodAttackEvent* const e);
};

#endif // EGODATTACKEVENTWIDGET_H
