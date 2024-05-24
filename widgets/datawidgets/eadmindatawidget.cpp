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
                        eLanguage::zeusText(14, 9), // see taxes
                        eViewMode::taxes,
                        window());
        addViewButton(mSeeTaxes);
    }

    eDataWidget::initialize();

    const auto inner = innerWidget();
    const int iw = inner->width();

    {
        const auto l = new eLabel(window());
        l->setNoPadding();
        l->setVerySmallFontSize();
        l->setText(eLanguage::zeusText(131, 0)); // tax rate
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
        mYields = new eLabel(window());
        mYields->setWrapWidth(iw);
        mYields->setWrapAlignment(eAlignment::hcenter);
        mYields->setNoPadding();
        mYields->setTinyFontSize();
        const auto yt = eLanguage::zeusText(60, 4); // yields an estimated
        const int y = mBoard.taxesPaidLastYear();
        const auto dr = eLanguage::zeusText(8, 1);
        mYields->setText(yt + " " + std::to_string(y) + " " + dr);
        mYields->fitContent();
        inner->addWidget(mYields);
        mYields->align(eAlignment::hcenter);
    }

    {
        mPerPop = new eLabel(window());
        mPerPop->setWrapWidth(iw);
        mPerPop->setWrapAlignment(eAlignment::hcenter);
        mPerPop->setNoPadding();
        mPerPop->setTinyFontSize();
        const auto pt = eLanguage::zeusText(60, 5); // of population visited by clerk
        const int paid = mBoard.peoplePaidTaxesLastYear();
        const int pop = mBoard.population();
        int per = pop == 0 ? 0 : std::round(100.*paid/pop);
        per = std::clamp(per, 0, 100);
        mPerPop->setText(std::to_string(per) + "% " + pt);
        mPerPop->fitContent();
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
            const auto yt = eLanguage::zeusText(60, 4); // yields an estimated
            const int y = mBoard.taxesPaidLastYear();
            const auto dr = eLanguage::zeusText(8, 1);
            mYields->setText(yt + " " + std::to_string(y) + " " + dr);
            mYields->fitContent();
            mYields->align(eAlignment::hcenter);
        }
        {
            const auto pt = eLanguage::zeusText(60, 5); // of population visited by clerk
            const int paid = mBoard.peoplePaidTaxesLastYear();
            const int pop = mBoard.population();
            int per = pop == 0 ? 0 : std::round(100.*paid/pop);
            per = std::clamp(per, 0, 100);
            mPerPop->setText(std::to_string(per) + "% " + pt);
            mPerPop->fitContent();
            mPerPop->align(eAlignment::hcenter);
        }
        const auto inner = innerWidget();
        inner->stackVertically();
    }
    eWidget::paintEvent(p);
}
