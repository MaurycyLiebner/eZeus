#include "eadmindatawidget.h"

#include "engine/egameboard.h"

#include "../elabel.h"

#include "../eupbutton.h"
#include "../edownbutton.h"

#include "eviewmodebutton.h"

#include "elanguage.h"
#include "estringhelpers.h"
#include "widgets/emultilinelabel.h"

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
            if(mTaxRate == eTaxRate::outrageous) return;
            const int wr = static_cast<int>(mTaxRate) + 1;
            setTaxRate(static_cast<eTaxRate>(wr));
        });
        w->addWidget(upButton);
        w->stackHorizontally();
        w->fitContent();
        inner->addWidget(w);
        w->align(eAlignment::hcenter);
    }
    setTaxRate(mBoard.taxRate());

    {
        auto yt = eLanguage::text("taxes_yield_data_widget");
        const int y = mBoard.taxesPaidLastYear();
        eStringHelpers::replace(yt, "%1", std::to_string(y));
        mYields = new eMultiLineLabel(window());
        mYields->setNoPadding();
        mYields->setTinyFontSize();
        mYields->setText(yt);
        inner->addWidget(mYields);
        mYields->align(eAlignment::hcenter);
    }

    {
        auto pt = eLanguage::text("population_visited_by_clerk_data_widget");
        const int paid = mBoard.peoplePaidTaxesLastYear();
        const int pop = mBoard.population();
        const int per = std::round(100.*paid/pop);
        eStringHelpers::replace(pt, "%1", std::to_string(per));
        mPerPop = new eMultiLineLabel(window());
        mPerPop->setNoPadding();
        mPerPop->setTinyFontSize();
        mPerPop->setText(pt);
        inner->addWidget(mPerPop);
        mPerPop->align(eAlignment::hcenter);
    }

    inner->stackVertically();
}

void eAdminDataWidget::setTaxRate(const eTaxRate tr) {
    mBoard.setTaxRate(tr);
    mTaxRate = tr;
    mTaxLabel->setText(eTaxRateHelpers::name(tr));
    mTaxLabel->fitContent();
    mTaxLabel->align(eAlignment::hcenter);
}

void eAdminDataWidget::paintEvent(ePainter& p) {
    const bool update = ((mTime++) % 20) == 0;
    if(update) {
        {
            auto yt = eLanguage::text("taxes_yield_data_widget");
            const int y = mBoard.taxesPaidLastYear();
            eStringHelpers::replace(yt, "%1", std::to_string(y));
            mYields->setText(yt);
            mYields->align(eAlignment::hcenter);
        }
        {
            auto pt = eLanguage::text("population_visited_by_clerk_data_widget");
            const int paid = mBoard.peoplePaidTaxesLastYear();
            const int pop = mBoard.population();
            int per = pop == 0 ? 0 : std::round(100.*paid/pop);
            per = std::clamp(per, 0, 100);
            eStringHelpers::replace(pt, "%1", std::to_string(per));
            mPerPop->setText(pt);
            mPerPop->align(eAlignment::hcenter);
        }
    }
    eWidget::paintEvent(p);
}
