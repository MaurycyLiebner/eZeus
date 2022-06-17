#include "eoverviewdatawidget.h"

#include "eviewmodebutton.h"

#include "widgets/egamewidget.h"

#include "elanguage.h"

void eOverviewDataWidget::initialize() {
    mSeeProblems = new eViewModeButton(
                     eLanguage::text("see_problems"),
                     eViewMode::problems,
                     window());
    addViewButton(mSeeProblems);

    mSeeRoads = new eViewModeButton(
                     eLanguage::text("see_roads"),
                     eViewMode::roads,
                     window());
    addViewButton(mSeeRoads);

    eDataWidget::initialize();
}
