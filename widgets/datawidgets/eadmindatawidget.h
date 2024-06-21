#ifndef EADMINDATAWIDGET_H
#define EADMINDATAWIDGET_H

#include "edatawidget.h"

#include "engine/etaxrate.h"

class eGameBoard;
class eLabel;
class eViewModeButton;
class eMultiLineLabel;

class eAdminDataWidget : public eDataWidget {
public:
    using eDataWidget::eDataWidget;

    void initialize();
protected:
    void paintEvent(ePainter& p);
private:
    void setTaxRate(const eTaxRate tr);

    eViewModeButton* mSeeTaxes = nullptr;

    eLabel* mTaxLabel = nullptr;
    eLabel* mYields = nullptr;
    eLabel* mPerPop = nullptr;

    eTaxRate mTaxRate{eTaxRate::normal};

    int mTime{0};
};

#endif // EADMINDATAWIDGET_H
