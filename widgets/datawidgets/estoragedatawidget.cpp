#include "estoragedatawidget.h"

#include "engine/egameboard.h"
#include "widgets/elabel.h"

#include "eviewmodebutton.h"

#include "elanguage.h"

eWidget* sdwColumn(eMainWindow* const window,
                   const eUIScale uiScale,
                   const int iMin, const int iMax,
                   const std::vector<eResourceType>& tps,
                   std::vector<eLabel*>& lbls) {
    const auto w0 = new eWidget(window);
    w0->setNoPadding();
    for(int i = iMin; i < iMax; i++) {
        const auto t = tps[i];
        const auto icon = eResourceTypeHelpers::icon(uiScale, t);
        const auto w = new eWidget(window);
        w->setNoPadding();
        const auto ic = new eLabel(window);
        ic->setTexture(icon);
        ic->setPadding(ic->padding()/4);
        ic->fitContent();
        const auto l = new eLabel("-", window);
        l->setTinyFontSize();
        l->setPadding(l->padding()/4);
        l->fitContent();
        lbls.push_back(l);

        w->addWidget(l);
        w->addWidget(ic);
        w->stackHorizontally();
        w->fitContent();
        ic->align(eAlignment::vcenter);
        l->align(eAlignment::vcenter);
        w0->addWidget(w);
    }
    w0->stackVertically();
    w0->fitContent();
    return w0;
}

void eStorageDataWidget::initialize() {
    {
        mSeeDistribution = new eViewModeButton(
                        eLanguage::text("see_distribution"),
                        eViewMode::taxes,
                        window());
        addViewButton(mSeeDistribution);
    }

    eDataWidget::initialize();

    const auto inner = innerWidget();

    const auto all = eResourceType::all & ~eResourceType::silver;
    const auto tps = eResourceTypeHelpers::extractResourceTypes(all);
    const auto res = resolution();
    const auto uiScale = res.uiScale();

    const int iMin0 = 0;
    const int iMax0 = tps.size()/2;
    const auto w0 = sdwColumn(window(), uiScale,
                              iMin0, iMax0, tps,
                              mResourceLabels);
    const int iMin1 = iMax0;
    const int iMax1 = tps.size();
    const auto w1 = sdwColumn(window(), uiScale,
                              iMin1, iMax1, tps,
                              mResourceLabels);

    const auto w = new eWidget(window());
    w->setNoPadding();
    w->addWidget(w0);
    w->addWidget(w1);
    w->stackHorizontally();
    w->fitContent();

    inner->addWidget(w);
    w->align(eAlignment::center);
}

void eStorageDataWidget::setBoard(eGameBoard* const b) {
    mBoard = b;
}

void eStorageDataWidget::paintEvent(ePainter& p) {
    const bool update = (++mTime % 200) == 0;
    if(update && mBoard) {
        mBoard->updateResources();
        const auto& src = mBoard->resources();
        const int iMax = mResourceLabels.size();
        for(int i = 0; i < iMax; i++) {
            const auto c = src[i].second;
            const auto l = mResourceLabels[i];
            l->setText(std::to_string(c));
        }
    }
    eWidget::paintEvent(p);
}
