#ifndef ERECEIVEREQUESTEVENTWIDGET_H
#define ERECEIVEREQUESTEVENTWIDGET_H

#include "../ewidget.h"

#include "gameEvents/ereceiverequestevent.h"

class eReceiveRequestEventWidget : public eWidget {
public:
    using eWidget::eWidget;

    void initialize(eReceiveRequestEvent* const e);
};

#endif // ERECEIVEREQUESTEVENTWIDGET_H
