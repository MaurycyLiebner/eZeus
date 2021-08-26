#include "epopulationdatawidget.h"

#include "engine/egameboard.h"

#include "../elabel.h"

void ePopulationDataWidget::initialize() {
    const auto p = new eLabel("Population:", window());
    p->setSmallFontSize();
    p->fitContent();
    mPopLabel = new eLabel("-", window());
    mPopLabel->fitContent();
    const auto v = new eLabel("Vacancies:", window());
    v->setSmallFontSize();
    v->fitContent();
    mVacLabel = new eLabel("-", window());
    mVacLabel->fitContent();
    const auto s = new eLabel("Settlers:", window());
    s->setSmallFontSize();
    s->fitContent();
    mSetLabel = new eLabel("-", window());
    mSetLabel->fitContent();

    addWidget(p);
    addWidget(mPopLabel);
    addWidget(v);
    addWidget(mVacLabel);
    addWidget(s);
    addWidget(mSetLabel);

    p->align(eAlignment::hcenter);
    v->align(eAlignment::hcenter);
    s->align(eAlignment::hcenter);
    mPopLabel->align(eAlignment::hcenter);
    mVacLabel->align(eAlignment::hcenter);
    mSetLabel->align(eAlignment::hcenter);
    layoutVertically();
}

void ePopulationDataWidget::setBoard(eGameBoard* const b) {
    mBoard = b;
}

void ePopulationDataWidget::paintEvent(ePainter& p) {
    const bool update = (++mTime % 200) == 0;
    if(update && mBoard) {
        const auto& popData = mBoard->populationData();

        const int p = popData.population();
        mPopLabel->setText(std::to_string(p));
        mPopLabel->fitContent();
        mPopLabel->align(eAlignment::hcenter);

        const int v = popData.vacancies();
        mVacLabel->setText(std::to_string(v));
        mVacLabel->fitContent();
        mVacLabel->align(eAlignment::hcenter);

        const int s = popData.settlers();
        mSetLabel->setText(std::to_string(s));
        mSetLabel->fitContent();
        mSetLabel->align(eAlignment::hcenter);
    }
    eWidget::paintEvent(p);
}
