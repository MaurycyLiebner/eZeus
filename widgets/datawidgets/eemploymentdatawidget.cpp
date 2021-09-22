#include "eemploymentdatawidget.h"

#include "engine/egameboard.h"

#include "../elabel.h"

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

        stackVertically();
    }
    eWidget::paintEvent(p);
}
