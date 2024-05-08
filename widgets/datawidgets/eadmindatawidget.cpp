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
        const auto l = new eLabel(eLanguage::text("tax_rate"), window());
        l->setNoPadding();
        l->setVerySmallFontSize();
        l->fitContent();
        inner->addWidget(l);
        l->align(eAlignment::hcenter);

        mTaxLabel = new eLabel(window());
        mTaxLabel->setNoPadding();
        mTaxLabel->setYellowFontColor();
        mTaxLabel->setVerySmallFontSize();
        mTaxLabel->setText(eTaxRateHelpers::name(eTaxRate::normal));
        mTaxLabel->fitContent();
        inner->addWidget(mTaxLabel);
        mTaxLabel->align(eAlignment::hcenter);

        const auto w = new eWidget(window());
        w->setNoPadding();
        const auto downButton = new eDownButton(window());
        downButton->setPressAction([this]() {
            if(mTaxRate == eTaxRate::none) return;
            const int wr = static_cast<int>(mTaxRate) - 1;
            setTaxRate(static_cast<eTaxRate>(wr));
        });
        w->addWidget(downButton);
        const auto upButton = new eUpButton(window());
        upButton->setPressAction([this]() {
            if(mTaxRate == eTaxRate::veryHigh) return;
            const int wr = static_cast<int>(mTaxRate) + 1;
            setTaxRate(static_cast<eTaxRate>(wr));
        });
        w->addWidget(upButton);
        w->stackHorizontally();
        w->fitContent();
        inner->addWidget(w);
        w->align(eAlignment::hcenter);
    }

    inner->stackVertically();
    setTaxRate(mBoard.taxRate());
}

void eAdminDataWidget::setTaxRate(const eTaxRate tr) {
    mBoard.setTaxRate(tr);
    mTaxRate = tr;
    mTaxLabel->setText(eTaxRateHelpers::name(tr));
    mTaxLabel->fitContent();
    mTaxLabel->align(eAlignment::hcenter);
}
