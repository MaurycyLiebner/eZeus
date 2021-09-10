#include "eculturedatawidget.h"

#include "eviewmodebutton.h"

void eCultureDataWidget::initialize() {
    mSeeActors = new eViewModeButton(
                     "See Actors",
                     eViewMode::actors,
                     window());

    addWidget(mSeeActors);
    mSeeActors->align(eAlignment::hcenter);


    mSeeAthletes = new eViewModeButton(
                     "See Athletes",
                     eViewMode::athletes,
                     window());

    addWidget(mSeeAthletes);
    mSeeAthletes->align(eAlignment::hcenter);


    mSeePhilosophers = new eViewModeButton(
                     "See Philosophers",
                     eViewMode::philosophers,
                     window());

    addWidget(mSeePhilosophers);
    mSeePhilosophers->align(eAlignment::hcenter);


    mSeeAllCulture = new eViewModeButton(
                     "See All Culture",
                     eViewMode::allCulture,
                     window());

    addWidget(mSeeAllCulture);
    mSeeAllCulture->align(eAlignment::hcenter);


    layoutVertically();
}

void eCultureDataWidget::setGameWidget(eGameWidget* const gw) {
    mSeeActors->setGameWidget(gw);
    mSeeAthletes->setGameWidget(gw);
    mSeePhilosophers->setGameWidget(gw);
    mSeeAllCulture->setGameWidget(gw);
}
