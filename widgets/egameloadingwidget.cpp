#include "egameloadingwidget.h"

#include "emainwindow.h"
#include "textures/egametextures.h"

eGameLoadingWidget::eGameLoadingWidget(eMainWindow* const window) :
    eWidget(window) {}

void eGameLoadingWidget::initialize() {
    mPB = new eProgressBar(window());
    mPB->fitContent();
    addWidget(mPB);
    mPB->align(eAlignment::center);

    mLabel = new eLabel("Waiting...", window());
    mLabel->fitContent();
    addWidget(mLabel);
    mLabel->align(eAlignment::hcenter);
    mLabel->setY(mPB->y() + 2*mLabel->height());

    mPB->setRange(0, eGameTextures::size());
}

void eGameLoadingWidget::setDoneAction(const eAction& a) {
    mDoneAction = a;
}

void eGameLoadingWidget::paintEvent(ePainter& p) {
    std::string text;
    const bool r = eGameTextures::loadNext(text);
    if(r) {
        if(mDoneAction) mDoneAction();
    } else {
        mPB->setValue(mPB->value() + 1);
        mLabel->setText(text);
    }

    eWidget::paintEvent(p);
}
