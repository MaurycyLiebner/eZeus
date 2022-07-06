#include "eadmindatawidget.h"

#include "engine/egameboard.h"

#include "../elabel.h"

#include "../eupbutton.h"
#include "../edownbutton.h"

#include "eviewmodebutton.h"

#include "elanguage.h"

void eAdminDataWidget::initialize() {
    {
        mSeeTaxes = new eViewModeButton(
                        eLanguage::text("see_taxes"),
                        eViewMode::taxes,
                        window());
        addViewButton(mSeeTaxes);
    }

    eDataWidget::initialize();

    const auto inner = innerWidget();
    {
        const auto l = new eLabel(eLanguage::text("taxes"), window());
        l->setSmallPadding();
        l->setVerySmallFontSize();
        l->fitContent();
        inner->addWidget(l);

        const auto w = new eWidget(window());
        w->setNoPadding();
        mTaxLabel = new eLabel(eTaxRateHelpers::name(eTaxRate::normal), window());
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
        inner->addWidget(w);
    }

    inner->stackVertically();
    setTaxRate(mBoard.taxRate());
}

void eAdminDataWidget::setTaxRate(const eTaxRate tr) {
    mBoard.setTaxRate(tr);
    mTaxRate = tr;
    mTaxLabel->setText(eTaxRateHelpers::name(tr));
}
