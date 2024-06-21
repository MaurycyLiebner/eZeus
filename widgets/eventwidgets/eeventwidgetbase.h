#ifndef EEVENTWIDGETBASE_H
#define EEVENTWIDGETBASE_H

#include "widgets/eframedwidget.h"

#include "pointers/estdselfref.h"

class eGameEvent;
class eGameBoard;

class eEventWidgetBase : public eFramedWidget {
public:
    using eFramedWidget::eFramedWidget;

    void initialize(const stdsptr<eGameEvent>& e);
};

#endif // EEVENTWIDGETBASE_H
