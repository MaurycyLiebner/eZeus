#ifndef EGIFTFROMEVENTWIDGET_H
#define EGIFTFROMEVENTWIDGET_H

#include "../ewidget.h"

#include "gameEvents/egiftfromevent.h"

class eGiftFromEventWidget : public eWidget {
public:
    using eWidget::eWidget;

    void initialize(eGiftFromEvent* const e);
};

#endif // EGIFTFROMEVENTWIDGET_H
