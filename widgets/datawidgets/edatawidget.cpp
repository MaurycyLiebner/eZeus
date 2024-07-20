#include "edatawidget.h"

#include "eviewmodebutton.h"
#include "widgets/ebasicbutton.h"
#include "elanguage.h"

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
    mMoreInfo = new eBasicButton(coll, window());
    frame->addWidget(mMoreInfo);
    mMoreInfo->align(eAlignment::right | eAlignment::bottom);
    mMoreInfo->move(mMoreInfo->x() - pp, mMoreInfo->y() - pp);
    mMoreInfo->setPressAction([this]() {
        openMoreInfoWiget();
    });
    mMoreInfo->setTooltip(eLanguage::zeusText(51, 79));
    mMoreInfo->hide();

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

void eDataWidget::shown() {
    mTime = 0;
}

void eDataWidget::addViewButton(eViewModeButton* const b) {
    mButtons.push_back(b);
}

int eDataWidget::spacing() const {
    const auto res = resolution();
    const double m = res.multiplier();
    return 3*m;
}

void eDataWidget::showMoreInfoButton() {
    mMoreInfo->show();
}

int eDataWidget::sCoverageToText(const int c) {
    if(c < 20) return 14; // terrible
    if(c < 40) return 13; // poor
    if(c < 60) return 12; // ok
    if(c < 80) return 11; // not bad
    return 10; // good
}
