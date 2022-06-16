#include "eculturedatawidget.h"

#include "eviewmodebutton.h"

#include "elanguage.h"

void eCultureDataWidget::initialize() {
    mSeePhilosophers = new eViewModeButton(
                     eLanguage::text("see_philosophers"),
                     eViewMode::philosophers,
                     window());
    addViewButton(mSeePhilosophers);

    mSeeAthletes = new eViewModeButton(
                     eLanguage::text("see_athletes"),
                     eViewMode::athletes,
                     window());
    addViewButton(mSeeAthletes);

    mSeeActors = new eViewModeButton(
                     eLanguage::text("see_actors"),
                     eViewMode::actors,
                     window());
    addViewButton(mSeeActors);

    mSeeAllCulture = new eViewModeButton(
                     eLanguage::text("see_all_culture"),
                     eViewMode::allCulture,
                     window());
    addViewButton(mSeeAllCulture);

    eDataWidget::initialize();
}
