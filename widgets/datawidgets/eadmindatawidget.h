#ifndef EADMINDATAWIDGET_H
#define EADMINDATAWIDGET_H

#include "edatawidget.h"

#include "engine/etaxrate.h"

class eGameBoard;
class eLabel;
class eViewModeButton;

class eAdminDataWidget : public eDataWidget {
public:
    using eDataWidget::eDataWidget;

    void initialize();
private:
    void setTaxRate(const eTaxRate tr);

    eViewModeButton* mSeeTaxes = nullptr;

    eLabel* mTaxLabel = nullptr;

    eTaxRate mTaxRate{eTaxRate::normal};
};

#endif // EADMINDATAWIDGET_H
