#include "ehygienesafetydatawidget.h"

#include "eviewmodebutton.h"

void eHygieneSafetyDataWidget::initialize() {
    mSeeWater = new eViewModeButton(
                     "See Water",
                     eViewMode::supplies,
                     window());

    addWidget(mSeeWater);
    mSeeWater->align(eAlignment::hcenter);


    mSeeHygiene = new eViewModeButton(
                     "See Hygiene",
                     eViewMode::hygiene,
                     window());

    addWidget(mSeeHygiene);
    mSeeHygiene->align(eAlignment::hcenter);


    mSeeHazards = new eViewModeButton(
                     "See Hazards",
                     eViewMode::hazards,
                     window());

    addWidget(mSeeHazards);
    mSeeHazards->align(eAlignment::hcenter);


    mSeeUnrest = new eViewModeButton(
                     "See Unrest",
                     eViewMode::unrest,
                     window());

    addWidget(mSeeUnrest);
    mSeeUnrest->align(eAlignment::hcenter);


    layoutVertically();
}

void eHygieneSafetyDataWidget::setGameWidget(eGameWidget* const gw) {
    mSeeWater->setGameWidget(gw);
    mSeeHygiene->setGameWidget(gw);
    mSeeHazards->setGameWidget(gw);
    mSeeUnrest->setGameWidget(gw);
}
