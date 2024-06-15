#include "edatawidget.h"

#include "eviewmodebutton.h"
#include "widgets/ebasicbutton.h"

eDataWidget::eDataWidget(eGameBoard& b, eMainWindow* const w) :
    eWidget(w), mBoard(b) {}

void eDataWidget::initialize() {
    int h = 0;
    for(const auto b : mButtons) {
        addWidget(b);
        b->align(eAlignment::hcenter);
        h += b->height();
    }

    const int pp = spacing();
    const auto space = new eWidget(window());
    space->setPadding(pp);
    space->fitContent();
    addWidget(space);

    const auto frame = new eFramedWidget(window());
    frame->setType(eFrameType::inner);
    frame->setHeight(height() - h + pp);
    frame->setWidth(width());
    frame->setTinyPadding();
    addWidget(frame);

    mInnerWidget = new eWidget(window());
    const int hhh = frame->height() - 2*pp;
    mInnerWidget->setHeight(hhh);
    const int www = frame->width() - 2*pp;
    mInnerWidget->setWidth(www);
    mInnerWidget->setNoPadding();
    frame->addWidget(mInnerWidget);
    mInnerWidget->move(pp, pp);

    const auto coll = &eInterfaceTextures::fMoreInfo;
    const auto moreInfo = new eBasicButton(coll, window());
    mInnerWidget->addWidget(moreInfo);
    moreInfo->align(eAlignment::right | eAlignment::bottom);
    moreInfo->setPressAction([this]() {
        openMoreInfoWiget();
    });

    stackVertically();
    setNoPadding();
    fitContent();
}

void eDataWidget::setGameWidget(eGameWidget* const gw) {
    mGW = gw;
    for(const auto b : mButtons) {
        b->setGameWidget(gw);
    }
}

void eDataWidget::addViewButton(eViewModeButton* const b) {
    mButtons.push_back(b);
}

int eDataWidget::spacing() const {
    const auto res = resolution();
    const double m = res.multiplier();
    return 3*m;
}

int eDataWidget::sCoverageToText(const int c) {
    if(c < 20) return 14; // terrible
    if(c < 40) return 13; // poor
    if(c < 60) return 12; // ok
    if(c < 80) return 11; // not bad
    return 10; // good
}
