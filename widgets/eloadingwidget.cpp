#include "eloadingwidget.h"

#include "emainwindow.h"
#include "textures/egametextures.h"

eLoadingWidget::eLoadingWidget(const int size,
                               const eLoader& loader,
                               eMainWindow* const window) :
    eWidget(window), mSize(size), mLoader(loader) {}

void eLoadingWidget::initialize() {
    mPB = new eProgressBar(window());
    mPB->fitContent();
    addWidget(mPB);
    mPB->align(eAlignment::center);

    mLabel = new eLabel("Waiting...", window());
    mLabel->fitContent();
    addWidget(mLabel);
    mLabel->align(eAlignment::hcenter);
    mLabel->setY(mPB->y() + 2*mLabel->height());

    mPB->setRange(0, mSize);
}

void eLoadingWidget::setDoneAction(const eAction& a) {
    mDoneAction = a;
}

void eLoadingWidget::paintEvent(ePainter& p) {
    std::string text;
    const bool r = mLoader(text);
    if(r) {
        if(mDoneAction) mDoneAction();
    } else {
        mPB->setValue(mPB->value() + 1);
        mLabel->setText(text);
    }

    eWidget::paintEvent(p);
}
