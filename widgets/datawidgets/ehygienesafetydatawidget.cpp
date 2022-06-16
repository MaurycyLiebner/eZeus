#include "ehygienesafetydatawidget.h"

#include "eviewmodebutton.h"

#include "elanguage.h"

void eHygieneSafetyDataWidget::initialize() {
    mSeeWater = new eViewModeButton(
                     eLanguage::text("see_water"),
                     eViewMode::water,
                     window());
    addViewButton(mSeeWater);


    mSeeHygiene = new eViewModeButton(
                     eLanguage::text("see_hygiene"),
                     eViewMode::hygiene,
                     window());
    addViewButton(mSeeHygiene);


    mSeeHazards = new eViewModeButton(
                     eLanguage::text("see_hazards"),
                     eViewMode::hazards,
                     window());
    addViewButton(mSeeHazards);


    mSeeUnrest = new eViewModeButton(
                     eLanguage::text("see_unrest"),
                     eViewMode::unrest,
                     window());

    addViewButton(mSeeUnrest);

    eDataWidget::initialize();
}
