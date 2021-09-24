#include "eadmindatawidget.h"

#include "engine/egameboard.h"

#include "../elabel.h"

#include "../eupbutton.h"
#include "../edownbutton.h"

void eAdminDataWidget::initialize() {
    {
        const auto l = new eLabel("Taxes:", window());
        l->setSmallPadding();
        l->setVerySmallFontSize();
        l->fitContent();
        addWidget(l);

        const auto w = new eWidget(window());
        w->setNoPadding();
        mTaxLabel = new eLabel("very high", window());
        mTaxLabel->setSmallPadding();
        mTaxLabel->setVerySmallFontSize();
        mTaxLabel->fitContent();
        w->addWidget(mTaxLabel);
        const auto upButton = new eUpButton(window());
        upButton->setPressAction([this]() {
            if(mTaxRate == eTaxRate::veryHigh) return;
            const int wr = static_cast<int>(mTaxRate) + 1;
            setTaxRate(static_cast<eTaxRate>(wr));
        });
        w->addWidget(upButton);
        const auto downButton = new eDownButton(window());
        downButton->setPressAction([this]() {
            if(mTaxRate == eTaxRate::none) return;
            const int wr = static_cast<int>(mTaxRate) - 1;
            setTaxRate(static_cast<eTaxRate>(wr));
        });
        w->addWidget(downButton);
        w->stackHorizontally();
        w->fitContent();
        upButton->align(eAlignment::vcenter);
        downButton->align(eAlignment::vcenter);
        addWidget(w);
    }

    stackVertically();
}

void eAdminDataWidget::setBoard(eGameBoard* const b) {
    mBoard = b;
    if(b) {
        setTaxRate(b->taxRate());
    }
}

void eAdminDataWidget::setTaxRate(const eTaxRate tr) {
    if(mBoard) {
        mBoard->setTaxRate(tr);
    }
    mTaxRate = tr;
    mTaxLabel->setText(eTaxRateHelpers::name(tr));
}
