#include "epopulationdatawidget.h"

#include "engine/egameboard.h"

#include "eviewmodebutton.h"

#include "edatalabel.h"

#include "elanguage.h"

void ePopulationDataWidget::initialize() {
    mSeeSupplies = new eViewModeButton(
                     eLanguage::text("see_supplies"),
                     eViewMode::supplies,
                     window());

    addWidget(mSeeSupplies);
    mSeeSupplies->align(eAlignment::hcenter);

    {
        const auto w = new eDataLabel(window());
        w->initialize(eLanguage::text("population"));
        mPopLabel = w->label();
        addWidget(w);
    }

    {
        const auto w = new eDataLabel(window());
        w->initialize(eLanguage::text("vacancies"));
        mVacLabel = w->label();
        addWidget(w);
    }

    stackVertically();
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

        const int v = popData.vacancies();
        mVacLabel->setText(std::to_string(v));
        mVacLabel->fitContent();
    }
    eWidget::paintEvent(p);
}
