#ifndef EADMINDATAWIDGET_H
#define EADMINDATAWIDGET_H

#include "../ewidget.h"

#include "engine/etaxrate.h"

class eGameBoard;
class eLabel;

class eAdminDataWidget : public eWidget {
public:
    using eWidget::eWidget;

    void initialize();

    void setBoard(eGameBoard* const b);
private:
    void setTaxRate(const eTaxRate tr);

    eGameBoard* mBoard = nullptr;

    eLabel* mTaxLabel = nullptr;

    eTaxRate mTaxRate{eTaxRate::normal};
};

#endif // EADMINDATAWIDGET_H
