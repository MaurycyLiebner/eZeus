#include "eemploymentdatawidget.h"

#include "engine/egameboard.h"

#include "../elabel.h"

#include "widgets/eupbutton.h"
#include "widgets/edownbutton.h"
#include "widgets/emultilinelabel.h"
#include "widgets/elinewidget.h"

#include "widgets/eframedwidget.h"

#include "eviewmodebutton.h"

#include "elanguage.h"

void eEmploymentDataWidget::initialize() {
    {
        mSeeIndustry = new eViewModeButton(
                        eLanguage::text("see_industry"),
                        eViewMode::industry,
                        window());
        addViewButton(mSeeIndustry);
    }

    eDataWidget::initialize();
    const auto inner = innerWidget();

    const auto& res = resolution();
    const double m = res.multiplier();

    const int pp = 3*m;

    const auto cw1 = new eWidget(window());
    {
        cw1->setNoPadding();

        const auto l = new eLabel(eLanguage::text("wage_rate"), window());
        l->setNoPadding();
        l->setVerySmallFontSize();
        l->fitContent();
        cw1->addWidget(l);

        mWageLabel = new eLabel(eWageRateHelpers::name(eWageRate::normal), window());
        mWageLabel->setYellowFontColor();
        mWageLabel->setNoPadding();
        mWageLabel->setVerySmallFontSize();
        mWageLabel->fitContent();
        cw1->addWidget(mWageLabel);

        const auto w = new eWidget(window());
        w->setNoPadding();
        const auto downButton = new eDownButton(window());
        downButton->setPressAction([this]() {
            if(mWageRate == eWageRate::none) return;
            const int wr = static_cast<int>(mWageRate) - 1;
            setWageRate(static_cast<eWageRate>(wr));
        });
        w->addWidget(downButton);
        const auto upButton = new eUpButton(window());
        upButton->setPressAction([this]() {
            if(mWageRate == eWageRate::veryHigh) return;
            const int wr = static_cast<int>(mWageRate) + 1;
            setWageRate(static_cast<eWageRate>(wr));
        });
        w->addWidget(upButton);
        w->stackHorizontally();
        w->fitContent();
        cw1->addWidget(w);

        cw1->stackVertically();
        cw1->fitContent();
        l->align(eAlignment::hcenter);
        mWageLabel->align(eAlignment::hcenter);
        w->align(eAlignment::hcenter);

        inner->addWidget(cw1);
        cw1->align(eAlignment::hcenter);
        cw1->setY(pp);
    }

    const auto cw2 = new eWidget(window());
    {
        cw2->setNoPadding();

        const auto ll = new eMultiLineLabel(window());
        ll->setVerySmallFontSize();
        ll->setNoPadding();
        ll->setText(eLanguage::text("projected_payroll"));
        cw2->addWidget(ll);

        mPensionsLabel = new eLabel(window());
        mPensionsLabel->setNoPadding();
        mPensionsLabel->setSmallFontSize();
        mPensionsLabel->setYellowFontColor();
        mPensionsLabel->setText("0 dr");
        mPensionsLabel->fitContent();
        cw2->addWidget(mPensionsLabel);

        cw2->stackVertically();
        cw2->fitContent();
        ll->align(eAlignment::hcenter);
        mPensionsLabel->align(eAlignment::hcenter);

        inner->addWidget(cw2);
        cw2->align(eAlignment::hcenter);
        cw2->setY(cw1->y() + cw1->height() + pp);
    }

    const auto l2 = new eLineWidget(window());
    l2->setNoPadding();
    l2->fitContent();
    l2->setWidth(inner->width());
    inner->addWidget(l2);
    l2->setY(cw2->y() + cw2->height() + pp);


    const auto cw3 = new eWidget(window());
    {
        cw3->setNoPadding();

        const auto ll = new eMultiLineLabel(window());
        ll->setVerySmallFontSize();
        ll->setNoPadding();
        ll->setText(eLanguage::text("employed_workforce"));
        cw3->addWidget(ll);

        mWorkforceLabel = new eLabel(window());
        mWorkforceLabel->setNoPadding();
        mWorkforceLabel->setSmallFontSize();
        mWorkforceLabel->setYellowFontColor();
        mWorkforceLabel->setText("0");
        mWorkforceLabel->fitContent();
        cw3->addWidget(mWorkforceLabel);

        cw3->stackVertically();
        cw3->fitContent();
        ll->align(eAlignment::hcenter);
        mWorkforceLabel->align(eAlignment::hcenter);

        inner->addWidget(cw3);
        cw3->align(eAlignment::hcenter);
        cw3->setY(l2->y() + l2->height() + pp);
    }

    const auto cw4 = new eWidget(window());
    {
        cw4->setNoPadding();

        const auto ll = new eLabel(window());
        ll->setVerySmallFontSize();
        ll->setNoPadding();
        ll->setText(eLanguage::text("unemployed"));
        ll->fitContent();
        cw4->addWidget(ll);

        mUnemployedNLabel = new eLabel(window());
        mUnemployedNLabel->setNoPadding();
        mUnemployedNLabel->setSmallFontSize();
        mUnemployedNLabel->setYellowFontColor();
        mUnemployedNLabel->setText("0");
        mUnemployedNLabel->fitContent();
        cw4->addWidget(mUnemployedNLabel);

        cw4->stackVertically();
        cw4->fitContent();
        ll->align(eAlignment::hcenter);
        mUnemployedNLabel->align(eAlignment::hcenter);

        inner->addWidget(cw4);
        cw4->align(eAlignment::hcenter);
        cw4->setY(cw3->y() + cw3->height() + pp);

        mUnemployedWidget = cw4;
        mUnemployedWidget->hide();
    }


    const auto cw5 = new eWidget(window());
    {
        cw5->setNoPadding();

        const auto ll = new eLabel(window());
        ll->setVerySmallFontSize();
        ll->setNoPadding();
        ll->setText(eLanguage::text("workers_needed"));
        ll->fitContent();
        cw5->addWidget(ll);

        mVacanciesNLabel = new eLabel(window());
        mVacanciesNLabel->setNoPadding();
        mVacanciesNLabel->setSmallFontSize();
        mVacanciesNLabel->setYellowFontColor();
        mVacanciesNLabel->setText("0");
        mVacanciesNLabel->fitContent();
        cw5->addWidget(mVacanciesNLabel);

        cw5->stackVertically();
        cw5->fitContent();
        ll->align(eAlignment::hcenter);
        mVacanciesNLabel->align(eAlignment::hcenter);

        inner->addWidget(cw5);
        cw5->align(eAlignment::hcenter);
        cw5->setY(cw3->y() + cw3->height() + pp);

        mVacanciesWidget = cw5;
    }

    setWageRate(mBoard.wageRate());
}

void eEmploymentDataWidget::paintEvent(ePainter& p) {
    const bool update = (++mTime % 20) == 0;
    if(update) {
        const auto& emplData = mBoard.employmentData();

        const bool vacsVisible = emplData.freeJobVacancies() > 0;
        mVacanciesWidget->setVisible(vacsVisible);
        mUnemployedWidget->setVisible(!vacsVisible);

        const int p = emplData.pensions();
        mPensionsLabel->setText(std::to_string(p) + " dr");
        mPensionsLabel->fitContent();
        mPensionsLabel->align(eAlignment::hcenter);

        const int w = emplData.employable();
        mWorkforceLabel->setText(std::to_string(w));
        mWorkforceLabel->fitContent();
        mWorkforceLabel->align(eAlignment::hcenter);

        const int v = emplData.freeJobVacancies();
        mVacanciesNLabel->setText(std::to_string(v));
        mVacanciesNLabel->fitContent();
        mVacanciesNLabel->align(eAlignment::hcenter);

        const int u = emplData.unemployed();
        const auto perStr = w ? "(" + std::to_string(100*u/w) + "%)" : "";
        mUnemployedNLabel->setText(std::to_string(u) + " " + perStr);
        mUnemployedNLabel->fitContent();
        mUnemployedNLabel->align(eAlignment::hcenter);
    }
    eDataWidget::paintEvent(p);
}

void eEmploymentDataWidget::setWageRate(const eWageRate wr) {
    mBoard.setWageRate(wr);
    mWageRate = wr;
    mWageLabel->setText(eWageRateHelpers::name(wr));
}
