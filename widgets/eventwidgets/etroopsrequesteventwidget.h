#ifndef ETROOPSREQUESTEVENTWIDGET_H
#define ETROOPSREQUESTEVENTWIDGET_H

#include "../ewidget.h"

#include "gameEvents/etroopsrequestevent.h"

class eTroopsRequestEventWidget : public eWidget {
public:
    using eWidget::eWidget;

    void initialize(eTroopsRequestEvent* const e);
};

#endif // ETROOPSREQUESTEVENTWIDGET_H
