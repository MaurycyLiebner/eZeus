#ifndef EAPPEALDATAWIDGET_H
#define EAPPEALDATAWIDGET_H

#include "../ewidget.h"

class eGameWidget;

class eAppealDataWidget : public eWidget {
public:
    using eWidget::eWidget;

    void initialize();

    void setGameWidget(eGameWidget* const gw);
private:
    eGameWidget* mGW = nullptr;
};

#endif // EAPPEALDATAWIDGET_H
