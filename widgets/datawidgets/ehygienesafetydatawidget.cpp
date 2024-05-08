#include "ehygienesafetydatawidget.h"

#include "eviewmodebutton.h"
#include "widgets/emultilinelabel.h"
#include "widgets/elinewidget.h"

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

    const auto inner = innerWidget();

    const auto chtitle = new eLabel(window());
    chtitle->setVerySmallFontSize();
    chtitle->setNoPadding();
    chtitle->setText(eLanguage::text("city_hygiene"));
    chtitle->fitContent();
    inner->addWidget(chtitle);
    chtitle->align(eAlignment::hcenter);

    mHygieneLabel = new eLabel(window());
    mHygieneLabel->setNoPadding();
    mHygieneLabel->setYellowFontColor();
    mHygieneLabel->setVerySmallFontSize();
    mHygieneLabel->setText(eLanguage::text("excellent"));
    mHygieneLabel->fitContent();
    inner->addWidget(mHygieneLabel);
    mHygieneLabel->align(eAlignment::hcenter);

    const auto spacer1 = new eWidget(window());
    spacer1->setHeight(spacing());
    inner->addWidget(spacer1);

    const auto l1 = new eLineWidget(window());
    l1->setNoPadding();
    l1->fitContent();
    l1->setWidth(inner->width());
    inner->addWidget(l1);

    const auto spacer2 = new eWidget(window());
    spacer2->setHeight(spacing());
    inner->addWidget(spacer2);

    {
        const auto unrestTitle = new eLabel(window());
        unrestTitle->setTinyFontSize();
        unrestTitle->setNoPadding();
        unrestTitle->setText(eLanguage::text("unrest"));
        unrestTitle->fitContent();
        inner->addWidget(unrestTitle);
        unrestTitle->align(eAlignment::hcenter);
    }
    {
        mUnrestLabel = new eMultiLineLabel(window());
        mUnrestLabel->setNoPadding();
        mUnrestLabel->setVerySmallFontSize();
        mUnrestLabel->setText(eLanguage::text("there_is_no_unrest"));

        inner->addWidget(mUnrestLabel);
        mUnrestLabel->align(eAlignment::hcenter);
    }
    inner->stackVertically();
}

void eHygieneSafetyDataWidget::paintEvent(ePainter& p) {
    const bool update = (++mTime % 20) == 0;
    if(update) {

    }
    eWidget::paintEvent(p);
}
