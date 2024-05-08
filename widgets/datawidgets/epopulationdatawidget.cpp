#include "epopulationdatawidget.h"

#include "engine/egameboard.h"

#include "eviewmodebutton.h"
#include "widgets/elinewidget.h"
#include "widgets/emultilinelabel.h"

#include "elanguage.h"

void ePopulationDataWidget::initialize() {
    mSeeSupplies = new eViewModeButton(
                     eLanguage::text("see_supplies"),
                     eViewMode::supplies,
                     window());
    addViewButton(mSeeSupplies);

    eDataWidget::initialize();

    const auto inner = innerWidget();

    const int pp = spacing();

    const auto cw1 = new eWidget(window());
    {
        cw1->setNoPadding();

        const auto hfor1 = new eLabel(window());
        hfor1->setVerySmallFontSize();
        hfor1->setNoPadding();
        hfor1->setText(eLanguage::text("housing_for1"));
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
        hfor2->setText(eLanguage::text("housing_for2"));
        hfor2->fitContent();
        cw1->addWidget(hfor2);

        cw1->stackVertically();
        cw1->fitContent();
        cw1->setWidth(inner->width());

        hfor1->align(eAlignment::hcenter);
        mVacLabel->align(eAlignment::hcenter);
        hfor2->align(eAlignment::hcenter);

        inner->addWidget(cw1);
    }

    const auto l1 = new eLineWidget(window());
    l1->setNoPadding();
    l1->fitContent();
    l1->setWidth(inner->width());
    inner->addWidget(l1);
    l1->setY(cw1->y() + cw1->height() + pp);

    {
        mPeopleDirection = new eMultiLineLabel(window());
        mPeopleDirection->setNoPadding();
        mPeopleDirection->setVerySmallFontSize();
        mPeopleDirection->setText(eLanguage::text("people_wish_to_come"));

        inner->addWidget(mPeopleDirection);
        mPeopleDirection->align(eAlignment::hcenter);
        mPeopleDirection->setY(l1->y() + l1->height() + pp);
    }

    const auto l2 = new eLineWidget(window());
    l2->setNoPadding();
    l2->fitContent();
    l2->setWidth(inner->width());
    inner->addWidget(l2);
    l2->setY(mPeopleDirection->y() + mPeopleDirection->height() + pp);

    {
        mImiLimitedW = new eWidget(window());
        mImiLimitedW->setNoPadding();

        const auto il1 = new eMultiLineLabel(window());
        il1->setVerySmallFontSize();
        il1->setNoPadding();
        il1->setText(eLanguage::text("immigration_limited_by"));
        mImiLimitedW->addWidget(il1);

        mImiLimitedReason = new eMultiLineLabel(window());
        mImiLimitedReason->setYellowFontColor();
        mImiLimitedReason->setVerySmallFontSize();
        mImiLimitedReason->setNoPadding();
        mImiLimitedReason->setText(eLanguage::text("lack_of_housing_vacs"));
        mImiLimitedW->addWidget(mImiLimitedReason);

        mImiLimitedW->stackVertically();
        mImiLimitedW->fitContent();
        mImiLimitedW->setWidth(inner->width() - 2*pp);

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

        const auto il1 = new eMultiLineLabel(window());
        il1->setVerySmallFontSize();
        il1->setNoPadding();
        il1->setText(eLanguage::text("newcomers_arrived"));
        cw4->addWidget(il1);

        cw4->stackVertically();
        cw4->fitContent();
        cw4->setWidth(inner->width() - 2*pp);

        il1->align(eAlignment::hcenter);
        mNewcomersLabel->align(eAlignment::hcenter);

        inner->addWidget(cw4);
        cw4->setY(l2->y() + l2->height() + pp);

        mNewcomersW = cw4;
        mNewcomersW->hide();
    }
}

void ePopulationDataWidget::paintEvent(ePainter& p) {
    const bool update = (++mTime % 20) == 0;
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
            pdtxt = "people_are_leaving_the_city";
        } else {
            pdtxt = "people_wish_to_come";
        }
        mPeopleDirection->setText(eLanguage::text(pdtxt));
        mPeopleDirection->fitContent();
        mPeopleDirection->align(eAlignment::hcenter);

        const int v = popData.vacancies();
        mVacLabel->setText(std::to_string(v));
        mVacLabel->fitContent();
        mVacLabel->align(eAlignment::hcenter);

        const auto husbData = mBoard.husbandryData();
        std::string ilrtxt;
        if(v <= 0) {
            ilrtxt = "lack_of_housing_vacs";
        } else if(husbData.storedFood() < 1) {
            ilrtxt = "lack_of_food";
        } else {
            ilrtxt = "lack_of_housing_vacs";
        }
        mImiLimitedReason->setText(eLanguage::text(ilrtxt));
    }
    eWidget::paintEvent(p);
}
