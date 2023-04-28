#ifndef EINVASIONEVENTWIDGET_H
#define EINVASIONEVENTWIDGET_H

#include "../ewidget.h"

#include "gameEvents/einvasionevent.h"

class eInvasionEventWidget : public eWidget {
public:
    using eWidget::eWidget;

    void initialize(eInvasionEvent* const e);
};

#endif // EINVASIONEVENTWIDGET_H
