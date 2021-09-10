#include "epopulationdatawidget.h"

#include "engine/egameboard.h"

#include "eviewmodebutton.h"

#include "../elabel.h"

void ePopulationDataWidget::initialize() {
    mSeeSupplies = new eViewModeButton(
                     "See Supplies",
                     eViewMode::supplies,
                     window());

    addWidget(mSeeSupplies);
    mSeeSupplies->align(eAlignment::hcenter);

    const auto p = new eLabel("Population:", window());
    p->setSmallFontSize();
    p->fitContent();
    mPopLabel = new eLabel("-", window());
    mPopLabel->setSmallFontSize();
    mPopLabel->fitContent();
    const auto v = new eLabel("Vacancies:", window());
    v->setSmallFontSize();
    v->fitContent();
    mVacLabel = new eLabel("-", window());
    mVacLabel->setSmallFontSize();
    mVacLabel->fitContent();

    addWidget(p);
    addWidget(mPopLabel);
    addWidget(v);
    addWidget(mVacLabel);

    p->align(eAlignment::hcenter);
    v->align(eAlignment::hcenter);
    mPopLabel->align(eAlignment::hcenter);
    mVacLabel->align(eAlignment::hcenter);
    layoutVertically();
}

void ePopulationDataWidget::setBoard(eGameBoard* const b) {
    mBoard = b;
}

void ePopulationDataWidget::setGameWidget(eGameWidget* const gw) {
    mSeeSupplies->setGameWidget(gw);
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
    }
    eWidget::paintEvent(p);
}
