#include "eemploymentdatawidget.h"

#include "engine/egameboard.h"

#include "../elabel.h"

#include "../eupbutton.h"
#include "../edownbutton.h"

void eEmploymentDataWidget::initialize() {
    {
        const auto w = new eDataLabel(window());
        w->initialize("Pensions: ");
        mPensionsLabel = w->label();
        addWidget(w);
    }

    {
        const auto w = new eDataLabel(window());
        w->initialize("Workforce: ");
        mWorkforceLabel = w->label();
        addWidget(w);
    }

    eDataLabel* jv = nullptr;
    {
        const auto w = new eDataLabel(window());
        w->initialize("Job Vacancies: ");
        mVacanciesNLabel = w->label();
        mVacanciesLabel = w;
        addWidget(w);
        jv = w;
    }

    {
        const auto l = new eLabel("Wages:", window());
        l->setSmallPadding();
        l->setVerySmallFontSize();
        l->fitContent();
        addWidget(l);

        const auto w = new eWidget(window());
        w->setNoPadding();
        mWageLabel = new eLabel("very high", window());
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
        addWidget(w);
    }

    stackVertically();


    {
        const auto w = new eDataLabel(window());
        w->initialize("Unemployed: ");
        mUnemployedNLabel = w->label();
        mUnemployedLabel = w;
        addWidget(w);

        w->setVisible(false);

        w->setX(jv->x());
        w->setY(jv->y());
    }
}

void eEmploymentDataWidget::setBoard(eGameBoard* const b) {
    mBoard = b;
    if(b) {
        setWageRate(b->wageRate());
    }
}

void eEmploymentDataWidget::paintEvent(ePainter& p) {
    const bool update = (++mTime % 200) == 0;
    if(update && mBoard) {
        const auto& emplData = mBoard->employmentData();

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
    eWidget::paintEvent(p);
}

void eEmploymentDataWidget::setWageRate(const eWageRate wr) {
    mWageRate = wr;
    mWageLabel->setText(eWageRateHelpers::name(wr));
}
