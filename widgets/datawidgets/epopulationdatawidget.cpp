#include "epopulationdatawidget.h"

#include "engine/egameboard.h"

#include "eviewmodebutton.h"
#include "edatalabel.h"
#include "widgets/elinewidget.h"

#include "elanguage.h"

void ePopulationDataWidget::initialize() {
    mSeeSupplies = new eViewModeButton(
                     eLanguage::text("see_supplies"),
                     eViewMode::supplies,
                     window());
    addViewButton(mSeeSupplies);

    eDataWidget::initialize();

    const auto inner = innerWidget();

    const auto& res = resolution();
    const double m = res.multiplier();

    const int pp = 3*m;

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
        cw1->setWidth(inner->width() - 2*pp);

        hfor1->align(eAlignment::hcenter);
        mVacLabel->align(eAlignment::hcenter);
        hfor2->align(eAlignment::hcenter);

        inner->addWidget(cw1);
        cw1->move(pp, pp);
    }

    const auto l1 = new eLineWidget(window());
    l1->setNoPadding();
    l1->fitContent();
    l1->setWidth(inner->width());
    inner->addWidget(l1);
    l1->setY(cw1->y() + cw1->height() + pp);

    const auto cw2 = new eLabel(window());
    {
        cw2->setNoPadding();
        cw2->setVerySmallFontSize();
        cw2->setWrapWidth(inner->width() - 2*pp);
        cw2->setText(eLanguage::text("people_wish_to_come"));
        cw2->fitContent();

        inner->addWidget(cw2);
        cw2->move(pp, l1->y() + l1->height() + pp);
    }

    const auto l2 = new eLineWidget(window());
    l2->setNoPadding();
    l2->fitContent();
    l2->setWidth(inner->width());
    inner->addWidget(l2);
    l2->setY(cw2->y() + cw2->height() + pp);

    const auto cw3 = new eWidget(window());
    {
        cw3->setNoPadding();

        const auto il1 = new eLabel(window());
        il1->setVerySmallFontSize();
        il1->setNoPadding();
        il1->setText(eLanguage::text("immigration_limited_by"));
        il1->fitContent();
        cw3->addWidget(il1);

        const auto il2 = new eLabel(window());
        il2->setYellowFontColor();
        il2->setVerySmallFontSize();
        il2->setNoPadding();
        il2->setText(eLanguage::text("lack_of_housing_vacs"));
        il2->fitContent();
        cw3->addWidget(il2);

        cw3->stackVertically();
        cw3->fitContent();
        cw3->setWidth(inner->width() - 2*pp);

        il1->align(eAlignment::hcenter);
        il2->align(eAlignment::hcenter);

        inner->addWidget(cw3);
        cw3->move(pp, l2->y() + l2->height() + pp);
    }
}

void ePopulationDataWidget::paintEvent(ePainter& p) {
    const bool update = (++mTime % 200) == 0;
    if(update) {
        const auto& popData = mBoard.populationData();

        const int v = popData.vacancies();
        mVacLabel->setText(std::to_string(v));
        mVacLabel->fitContent();
    }
    eWidget::paintEvent(p);
}
