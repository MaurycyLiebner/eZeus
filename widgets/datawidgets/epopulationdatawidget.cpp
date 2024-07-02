#include "epopulationdatawidget.h"

#include "engine/egameboard.h"

#include "eviewmodebutton.h"
#include "widgets/elinewidget.h"
#include "widgets/emultilinelabel.h"

#include "elanguage.h"

void ePopulationDataWidget::initialize() {
    mSeeSupplies = new eViewModeButton(
                     eLanguage::zeusText(14, 1),
                     eViewMode::supplies,
                     window());
    addViewButton(mSeeSupplies);

    eDataWidget::initialize();

    const auto inner = innerWidget();
    const int iw = inner->width();

    const int pp = spacing();

    const auto cw1 = new eWidget(window());
    {
        cw1->setNoPadding();

        const auto hfor1 = new eLabel(window());
        hfor1->setVerySmallFontSize();
        hfor1->setNoPadding();
        hfor1->setText(eLanguage::zeusText(55, 8)); // housing for
        hfor1->fitContent();
        cw1->addWidget(hfor1);

        mVacLabel = new eLabel("0", window());
        mVacLabel->setNoPadding();
        mVacLabel->setYellowFontColor();
        mVacLabel->fitContent();
        cw1->addWidget(mVacLabel);

        const auto hfor2 = new eLabel(window());
        hfor2->setVerySmallFontSize();
        hfor2->setNoPadding();
        hfor2->setText(eLanguage::zeusText(55, 9)); // more people
        hfor2->fitContent();
        cw1->addWidget(hfor2);

        cw1->stackVertically();
        cw1->fitContent();
        cw1->setWidth(iw);

        hfor1->align(eAlignment::hcenter);
        mVacLabel->align(eAlignment::hcenter);
        hfor2->align(eAlignment::hcenter);

        inner->addWidget(cw1);
    }

    const auto l1 = new eLineWidget(window());
    l1->setNoPadding();
    l1->fitContent();
    l1->setWidth(iw);
    inner->addWidget(l1);
    l1->setY(cw1->y() + cw1->height() + pp);

    {
        mPeopleDirection = new eLabel(window());
        mPeopleDirection->setWrapWidth(iw);
        mPeopleDirection->setWrapAlignment(eAlignment::hcenter);
        mPeopleDirection->setNoPadding();
        mPeopleDirection->setVerySmallFontSize();
        mPeopleDirection->setText(eLanguage::zeusText(55, 20)); // people wish to come

        inner->addWidget(mPeopleDirection);
        mPeopleDirection->fitContent();
        mPeopleDirection->align(eAlignment::hcenter);
        mPeopleDirection->setY(l1->y() + l1->height() + pp);
    }

    const auto l2 = new eLineWidget(window());
    l2->setNoPadding();
    l2->fitContent();
    l2->setWidth(iw);
    inner->addWidget(l2);
    l2->setY(mPeopleDirection->y() + mPeopleDirection->height() + pp);

    {
        mImiLimitedW = new eWidget(window());
        mImiLimitedW->setNoPadding();

        const auto il1 = new eLabel(window());
        il1->setWrapWidth(iw);
        il1->setWrapAlignment(eAlignment::hcenter);
        il1->setVerySmallFontSize();
        il1->setNoPadding();
        il1->setText(eLanguage::zeusText(55, 12)); // immigration limited by
        il1->fitContent();
        mImiLimitedW->addWidget(il1);

        mImiLimitedReason = new eLabel(window());
        mImiLimitedReason->setWrapWidth(iw);
        mImiLimitedReason->setWrapAlignment(eAlignment::hcenter);
        mImiLimitedReason->setYellowFontColor();
        mImiLimitedReason->setVerySmallFontSize();
        mImiLimitedReason->setNoPadding();
        mImiLimitedReason->setText(eLanguage::zeusText(55, 13)); // lack of housing vacancies
        mImiLimitedReason->fitContent();
        mImiLimitedW->addWidget(mImiLimitedReason);


        mImiLimitedW->stackVertically();
        mImiLimitedW->fitContent();
        mImiLimitedW->setWidth(iw - 2*pp);

        il1->align(eAlignment::hcenter);
        mImiLimitedReason->align(eAlignment::hcenter);

        inner->addWidget(mImiLimitedW);
        mImiLimitedW->setY(l2->y() + l2->height() + pp);
    }


    const auto cw4 = new eWidget(window());
    {
        cw4->setNoPadding();

        mNewcomersLabel = new eLabel("0", window());
        mNewcomersLabel->setNoPadding();
        mNewcomersLabel->setYellowFontColor();
        mNewcomersLabel->fitContent();
        cw4->addWidget(mNewcomersLabel);

        const auto il1 = new eLabel(window());
        il1->setWrapWidth(iw);
        il1->setWrapAlignment(eAlignment::hcenter);
        il1->setVerySmallFontSize();
        il1->setNoPadding();
        il1->setText(eLanguage::zeusText(55, 10)); // newcomers arrived this month
        il1->fitContent();
        cw4->addWidget(il1);

        cw4->stackVertically();
        cw4->fitContent();
        cw4->setWidth(iw - 2*pp);

        il1->align(eAlignment::hcenter);
        mNewcomersLabel->align(eAlignment::hcenter);

        inner->addWidget(cw4);
        cw4->setY(l2->y() + l2->height() + pp);

        mNewcomersW = cw4;
        mNewcomersW->hide();
    }
}

void ePopulationDataWidget::paintEvent(ePainter& p) {
    const bool update = ((mTime++) % 20) == 0;
    if(update) {
        const auto& popData = mBoard.populationData();

        const int a = popData.arrived();
        mImiLimitedW->setVisible(a <= 0);
        mNewcomersW->setVisible(a > 0);
        mNewcomersLabel->setText(std::to_string(a));
        mNewcomersLabel->fitContent();
        mNewcomersLabel->align(eAlignment::hcenter);

        const int l = popData.left();
        std::string pdtxt;
        if(l > a) {
            pdtxt = eLanguage::zeusText(55, 21); // people are leaving the city
        } else if(a > l) {
            pdtxt = eLanguage::zeusText(55, 20); // people with to come to the city
        }
        if(!pdtxt.empty()) {
            mPeopleDirection->setText(pdtxt);
            mPeopleDirection->fitContent();
            mPeopleDirection->align(eAlignment::hcenter);
        }

        const int v = popData.vacancies();
        mVacLabel->setText(std::to_string(v));
        mVacLabel->fitContent();
        mVacLabel->align(eAlignment::hcenter);

        const auto limit = mBoard.immigrationLimit();
        std::string ilrtxt;
        if(v <= 0) {
            ilrtxt = eLanguage::zeusText(55, 13); // lack of housing vacancies
        } else if(limit == eImmigrationLimitedBy::lowWages) {
            ilrtxt = eLanguage::zeusText(55, 14);
        } else if(limit == eImmigrationLimitedBy::unemployment) {
            ilrtxt = eLanguage::zeusText(55, 15);
        } else if(limit == eImmigrationLimitedBy::lackOfFood) {
            ilrtxt = eLanguage::zeusText(55, 16);
        } else if(limit == eImmigrationLimitedBy::highTaxes) {
            ilrtxt = eLanguage::zeusText(55, 17);
        } else if(limit == eImmigrationLimitedBy::prolongedDebt) {
            ilrtxt = eLanguage::zeusText(55, 18);
        } else if(limit == eImmigrationLimitedBy::excessiveMilitaryService) {
            ilrtxt = eLanguage::zeusText(55, 19);
        } else {
            ilrtxt = eLanguage::zeusText(55, 13); // lack of housing vacancies
        }
        mImiLimitedReason->setText(ilrtxt);
        mImiLimitedReason->fitContent();
        mImiLimitedReason->align(eAlignment::hcenter);
    }
    eWidget::paintEvent(p);
}
