#ifndef EMILITARYDATAWIDGET_H
#define EMILITARYDATAWIDGET_H

#include "edatawidget.h"

class eGameBoard;

class eMilitaryDataWidget : public eDataWidget {
public:
    using eDataWidget::eDataWidget;

    void initialize();
private:
    eViewModeButton* mSeeSecurity = nullptr;
};

#endif // EMILITARYDATAWIDGET_H
