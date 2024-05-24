#include "estoragedatawidget.h"

#include "engine/egameboard.h"
#include "widgets/elabel.h"

#include "eviewmodebutton.h"

#include "elanguage.h"

eWidget* eStorageDataWidget::sdwColumn(
        const eUIScale uiScale,
        const int iMin, const int iMax,
        const std::vector<eResourceType>& tps,
        std::vector<eLabel*>& lbls) {
    const int pp = spacing();
    const auto w0 = new eWidget(window());
    w0->setNoPadding();
    for(int i = iMin; i < iMax; i++) {
        const auto t = tps[i];
        const auto icon = eResourceTypeHelpers::icon(uiScale, t);
        const auto w = new eWidget(window());
        w->setNoPadding();
        const auto ic = new eLabel(window());
        ic->setTexture(icon);
        ic->setNoPadding();
        ic->fitContent();

        const auto lw = new eWidget(window());
        lw->setNoPadding();
        const auto l = new eLabel("-", window());
        l->setTinyFontSize();
        l->setNoPadding();
        l->fitContent();
        lbls.push_back(l);
        lw->addWidget(l);
        l->align(eAlignment::right);

        w->addWidget(lw);
        w->addWidget(ic);
        w->stackHorizontally(2*pp);
        w->fitContent();
        ic->align(eAlignment::vcenter);
        l->align(eAlignment::vcenter);
        lw->align(eAlignment::vcenter);
        w0->addWidget(w);
    }
    w0->stackVertically(2*pp);
    w0->fitContent();
    return w0;
}

void eStorageDataWidget::initialize() {
    {
        mSeeDistribution = new eViewModeButton(
                        eLanguage::zeusText(14, 4),
                        eViewMode::distribution,
                        window());
        addViewButton(mSeeDistribution);
    }

    eDataWidget::initialize();

    const auto inner = innerWidget();

    const auto all = mBoard.supportedResources();
    const auto tps = eResourceTypeHelpers::extractResourceTypes(all);
    const auto res = resolution();
    const auto uiScale = res.uiScale();

    const int iMin0 = 0;
    const int iMax0 = tps.size()/2 + 1;
    const auto w0 = sdwColumn(uiScale,
                              iMin0, iMax0, tps,
                              mResourceLabels);
    const int iMin1 = iMax0;
    const int iMax1 = tps.size();
    const auto w1 = sdwColumn(uiScale,
                              iMin1, iMax1, tps,
                              mResourceLabels);

    const auto w = new eWidget(window());
    w->setNoPadding();
    w->addWidget(w0);
    w->addWidget(w1);
    const int pp = spacing();
    w->stackHorizontally(10*pp);
    w->fitContent();

    inner->addWidget(w);
    w->align(eAlignment::center);
    w->setX(w->x() + 2*pp);
}

void eStorageDataWidget::paintEvent(ePainter& p) {
    const bool update = ((mTime++) % 20) == 0;
    if(update) {
        mBoard.updateResources();
        const auto& src = mBoard.resources();
        const int iMax = mResourceLabels.size();
        for(int i = 0; i < iMax; i++) {
            const auto c = src[i].second;
            const auto l = mResourceLabels[i];
            l->setText(std::to_string(c));
            l->fitContent();
            l->align(eAlignment::right);
        }
    }
    eWidget::paintEvent(p);
}
