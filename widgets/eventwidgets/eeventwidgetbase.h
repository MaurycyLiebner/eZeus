#ifndef EEVENTWIDGETBASE_H
#define EEVENTWIDGETBASE_H

#include "widgets/eframedwidget.h"

#include "pointers/estdselfref.h"

class eGameEventCycle;
class eGameBoard;

class eEventWidgetBase : public eFramedWidget {
public:
    using eFramedWidget::eFramedWidget;

    void initialize(const stdsptr<eGameEventCycle>& e,
                    eGameBoard* const boardPtr);
};

#endif // EEVENTWIDGETBASE_H
