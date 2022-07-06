#include "eemploymentdatawidget.h"

#include "engine/egameboard.h"

#include "../elabel.h"

#include "../eupbutton.h"
#include "../edownbutton.h"

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

    {
        const auto w = new eDataLabel(window());
        w->initialize(eLanguage::text("pensions"));
        mPensionsLabel = w->label();
        inner->addWidget(w);
    }

    {
        const auto w = new eDataLabel(window());
        w->initialize(eLanguage::text("workforce"));
        mWorkforceLabel = w->label();
        inner->addWidget(w);
    }

    eDataLabel* jv = nullptr;
    {
        const auto w = new eDataLabel(window());
        w->initialize(eLanguage::text("job_vacancies"));
        mVacanciesNLabel = w->label();
        mVacanciesLabel = w;
        inner->addWidget(w);
        jv = w;
    }

    {
        const auto l = new eLabel(eLanguage::text("wages"), window());
        l->setSmallPadding();
        l->setVerySmallFontSize();
        l->fitContent();
        inner->addWidget(l);

        const auto w = new eWidget(window());
        w->setNoPadding();
        mWageLabel = new eLabel(eWageRateHelpers::name(eWageRate::normal), window());
        mWageLabel->setSmallPadding();
        mWageLabel->setVerySmallFontSize();
        mWageLabel->fitContent();
        w->addWidget(mWageLabel);
        const auto upButton = new eUpButton(window());
        upButton->setPressAction([this]() {
            if(mWageRate == eWageRate::veryHigh) return;
            const int wr = static_cast<int>(mWageRate) + 1;
            setWageRate(static_cast<eWageRate>(wr));
        });
        w->addWidget(upButton);
        const auto downButton = new eDownButton(window());
        downButton->setPressAction([this]() {
            if(mWageRate == eWageRate::none) return;
            const int wr = static_cast<int>(mWageRate) - 1;
            setWageRate(static_cast<eWageRate>(wr));
        });
        w->addWidget(downButton);
        w->stackHorizontally();
        w->fitContent();
        upButton->align(eAlignment::vcenter);
        downButton->align(eAlignment::vcenter);
        inner->addWidget(w);
    }

    inner->stackVertically();


    {
        const auto w = new eDataLabel(window());
        w->initialize(eLanguage::text("unemployed"));
        mUnemployedNLabel = w->label();
        mUnemployedLabel = w;
        inner->addWidget(w);

        w->setVisible(false);

        w->setX(jv->x());
        w->setY(jv->y());
    }

    setWageRate(mBoard.wageRate());
}

void eEmploymentDataWidget::paintEvent(ePainter& p) {
    const bool update = (++mTime % 200) == 0;
    if(update) {
        const auto& emplData = mBoard.employmentData();

        const bool vacsVisible = emplData.freeJobVacancies() > 0;
        mVacanciesLabel->setVisible(vacsVisible);
        mUnemployedLabel->setVisible(!vacsVisible);

        const int p = emplData.pensions();
        mPensionsLabel->setText(std::to_string(p));
        mPensionsLabel->fitContent();

        const int w = emplData.employable();
        mWorkforceLabel->setText(std::to_string(w));
        mWorkforceLabel->fitContent();

        const int v = emplData.freeJobVacancies();
        mVacanciesNLabel->setText(std::to_string(v));
        mVacanciesNLabel->fitContent();

        const int u = emplData.unemployed();
        mUnemployedNLabel->setText(std::to_string(u));
        mUnemployedNLabel->fitContent();
    }
    eDataWidget::paintEvent(p);
}

void eEmploymentDataWidget::setWageRate(const eWageRate wr) {
    mBoard.setWageRate(wr);
    mWageRate = wr;
    mWageLabel->setText(eWageRateHelpers::name(wr));
}
