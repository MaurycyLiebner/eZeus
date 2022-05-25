#include "ehygienesafetydatawidget.h"

#include "eviewmodebutton.h"

#include "elanguage.h"

void eHygieneSafetyDataWidget::initialize() {
    mSeeWater = new eViewModeButton(
                     eLanguage::text("see_water"),
                     eViewMode::water,
                     window());

    addWidget(mSeeWater);
    mSeeWater->align(eAlignment::hcenter);


    mSeeHygiene = new eViewModeButton(
                     eLanguage::text("see_hygiene"),
                     eViewMode::hygiene,
                     window());

    addWidget(mSeeHygiene);
    mSeeHygiene->align(eAlignment::hcenter);


    mSeeHazards = new eViewModeButton(
                     eLanguage::text("see_hazards"),
                     eViewMode::hazards,
                     window());

    addWidget(mSeeHazards);
    mSeeHazards->align(eAlignment::hcenter);


    mSeeUnrest = new eViewModeButton(
                     eLanguage::text("see_unrest"),
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
