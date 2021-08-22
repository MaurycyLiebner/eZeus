#include "eemploymentdatawidget.h"

#include "engine/egameboard.h"

#include "../elabel.h"

void eEmploymentDataWidget::initialize() {
    const auto p = new eLabel("Pensions:", window());
    p->setSmallFontSize();
    p->fitContent();
    mPensionsLabel = new eLabel("-", window());
    mPensionsLabel->fitContent();
    mUnemployedLabel = new eLabel("Unemploed:", window());
    mUnemployedLabel->setSmallFontSize();
    mUnemployedLabel->fitContent();
    mUnemployedNLabel = new eLabel("-", window());
    mUnemployedNLabel->fitContent();
    mVacanciesLabel = new eLabel("Job Vacancies:", window());
    mVacanciesLabel->setSmallFontSize();
    mVacanciesLabel->fitContent();
    mVacanciesNLabel = new eLabel("-", window());
    mVacanciesNLabel->fitContent();

    addWidget(p);
    addWidget(mPensionsLabel);
    addWidget(mUnemployedLabel);
    addWidget(mUnemployedNLabel);
    layoutVertically();

    addWidget(mVacanciesLabel);
    mVacanciesLabel->setY(mUnemployedLabel->y());
    addWidget(mVacanciesNLabel);
    mVacanciesNLabel->setY(mUnemployedNLabel->y());
    mVacanciesLabel->hide();
    mVacanciesNLabel->hide();

    p->align(eAlignment::hcenter);
    mUnemployedLabel->align(eAlignment::hcenter);
    mVacanciesLabel->align(eAlignment::hcenter);
    mPensionsLabel->align(eAlignment::hcenter);
    mUnemployedNLabel->align(eAlignment::hcenter);
    mVacanciesNLabel->align(eAlignment::hcenter);
}

void eEmploymentDataWidget::setBoard(eGameBoard* const b) {
    mBoard = b;
}

void eEmploymentDataWidget::paintEvent(ePainter& p) {
    const bool update = (++mTime % 200) == 0;
    if(update && mBoard) {
        const auto& emplData = mBoard->employmentData();

        const bool vacsVisible = emplData.jobVacancies() > 0;
        mVacanciesLabel->setVisible(vacsVisible);
        mVacanciesNLabel->setVisible(vacsVisible);

        mUnemployedLabel->setVisible(!vacsVisible);
        mUnemployedNLabel->setVisible(!vacsVisible);

        const int p = emplData.pensions();
        mPensionsLabel->setText(std::to_string(p));
        mPensionsLabel->fitContent();

        const int v = emplData.jobVacancies();
        mVacanciesNLabel->setText(std::to_string(v));
        mVacanciesNLabel->fitContent();

        const int u = emplData.pensions();
        mUnemployedNLabel->setText(std::to_string(u));
        mUnemployedNLabel->fitContent();
    }
    eWidget::paintEvent(p);
}
