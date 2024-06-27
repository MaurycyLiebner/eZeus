#ifndef EGODDISASTEREVENTWIDGET_H
#define EGODDISASTEREVENTWIDGET_H

#include "../ewidget.h"

class eGodDisasterEvent;

class eGodDisasterEventWidget : public eWidget {
public:
    using eWidget::eWidget;

    void initialize(eGodDisasterEvent* const e);
};

#endif // EGODDISASTEREVENTWIDGET_H
