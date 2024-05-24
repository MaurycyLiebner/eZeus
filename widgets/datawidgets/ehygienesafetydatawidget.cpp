#include "ehygienesafetydatawidget.h"

#include "eviewmodebutton.h"
#include "widgets/emultilinelabel.h"
#include "widgets/elinewidget.h"
#include "engine/egameboard.h"

#include "elanguage.h"

void eHygieneSafetyDataWidget::initialize() {
    mSeeWater = new eViewModeButton(
                     eLanguage::zeusText(14, 5),
                     eViewMode::water,
                     window());
    addViewButton(mSeeWater);


    mSeeHygiene = new eViewModeButton(
                     eLanguage::zeusText(14, 6),
                     eViewMode::hygiene,
                     window());
    addViewButton(mSeeHygiene);


    mSeeHazards = new eViewModeButton(
                     eLanguage::zeusText(14, 7),
                     eViewMode::hazards,
                     window());
    addViewButton(mSeeHazards);


    mSeeUnrest = new eViewModeButton(
                     eLanguage::zeusText(14, 8),
                     eViewMode::unrest,
                     window());

    addViewButton(mSeeUnrest);

    eDataWidget::initialize();

    const auto inner = innerWidget();
    const int iw = inner->width();

    const auto chtitle = new eLabel(window());
    chtitle->setVerySmallFontSize();
    chtitle->setNoPadding();
    chtitle->setText(eLanguage::zeusText(56, 1)); // city hygiene
    chtitle->fitContent();
    inner->addWidget(chtitle);
    chtitle->align(eAlignment::hcenter);

    mHygieneLabel = new eLabel(window());
    mHygieneLabel->setNoPadding();
    mHygieneLabel->setYellowFontColor();
    mHygieneLabel->setVerySmallFontSize();
    mHygieneLabel->setText(eLanguage::zeusText(56, 10)); // excellent
    mHygieneLabel->fitContent();
    inner->addWidget(mHygieneLabel);
    mHygieneLabel->align(eAlignment::hcenter);

    const auto spacer1 = new eWidget(window());
    spacer1->setHeight(spacing());
    inner->addWidget(spacer1);

    const auto l1 = new eLineWidget(window());
    l1->setNoPadding();
    l1->fitContent();
    l1->setWidth(iw);
    inner->addWidget(l1);

    const auto spacer2 = new eWidget(window());
    spacer2->setHeight(spacing());
    inner->addWidget(spacer2);

    {
        const auto unrestTitle = new eLabel(window());
        unrestTitle->setTinyFontSize();
        unrestTitle->setNoPadding();
        unrestTitle->setText(eLanguage::zeusText(56, 17)); // unrest
        unrestTitle->fitContent();
        inner->addWidget(unrestTitle);
        unrestTitle->align(eAlignment::hcenter);
    }
    {
        mUnrestLabel = new eLabel(window());
        mUnrestLabel->setWrapWidth(iw);
        mUnrestLabel->setWrapAlignment(eAlignment::hcenter);
        mUnrestLabel->setNoPadding();
        mUnrestLabel->setVerySmallFontSize();
        mUnrestLabel->setYellowFontColor();
        mUnrestLabel->setText(eLanguage::zeusText(56, 23)); // no unrest
        mUnrestLabel->fitContent();

        inner->addWidget(mUnrestLabel);
        mUnrestLabel->align(eAlignment::hcenter);
    }
    inner->stackVertically();
}

void eHygieneSafetyDataWidget::paintEvent(ePainter& p) {
    const bool update = ((mTime++) % 20) == 0;
    if(update) {
        const int hygiene = mBoard.health();
        int hString = -1;
        if(hygiene > 90) {
            hString = 12;
        } else if(hygiene > 85) {
            hString = 11;
        } else if(hygiene > 80) {
            hString = 10;
        } else if(hygiene > 75) {
            hString = 9;
        } else if(hygiene > 70) {
            hString = 8;
        } else if(hygiene > 65) {
            hString = 7;
        } else if(hygiene > 60) {
            hString = 6;
        } else if(hygiene > 55) {
            hString = 5;
        } else if(hygiene > 50) {
            hString = 4;
        } else if(hygiene > 45) {
            hString = 3;
        } else {
            hString = 2;
        }
        mHygieneLabel->setText(eLanguage::zeusText(56, hString));
        mHygieneLabel->fitContent();
        mHygieneLabel->align(eAlignment::hcenter);

        const int unrest = mBoard.unrest();
        int uString = -1;
        if(unrest > 8) {
            uString = 19;
        } else if(unrest > 6) {
            uString = 20;
        } else if(unrest > 4) {
            uString = 21;
        } else if(unrest > 0) {
            uString = 22;
        } else {
            uString = 23;
        }
        mUnrestLabel->setText(eLanguage::zeusText(56, uString));
        mUnrestLabel->fitContent();
        mUnrestLabel->align(eAlignment::hcenter);
    }
    eWidget::paintEvent(p);
}
