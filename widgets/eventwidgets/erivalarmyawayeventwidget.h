#ifndef ERIVALARMYAWAYEVENTWIDGET_H
#define ERIVALARMYAWAYEVENTWIDGET_H

#include "../ewidget.h"

class eRivalArmyAwayEvent;

class eRivalArmyAwayEventWidget : public eWidget {
public:
    using eWidget::eWidget;

    void initialize(eRivalArmyAwayEvent* const e);
};

#endif // ERIVALARMYAWAYEVENTWIDGET_H
