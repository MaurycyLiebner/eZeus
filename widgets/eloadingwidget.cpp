#include "eloadingwidget.h"

#include "emainwindow.h"
#include "textures/egametextures.h"
#include "textures/einterfacetextures.h"

eLoadingWidget::eLoadingWidget(const int size,
                               const eLoader& loader,
                               eMainWindow* const window) :
    eWidget(window), mSize(size), mLoader(loader) {
}

void eLoadingWidget::initialize() {
    const auto bg = new eLabel(window());

    const auto& intrfc = eGameTextures::interface();

    const auto res = resolution();
    int iRes;
    switch(res) {
    case eRes::p2160:
    case eRes::p1440:
        iRes = 2;
        break;
    case eRes::p1080:
    case eRes::p720:
        iRes = 1;
        break;
    case eRes::p480:
        iRes = 0;
        break;
    }

    const auto& texs = intrfc[iRes];
    bg->setTexture(texs.fLoadImage);
    bg->fitContent();
    addWidget(bg);
    bg->align(eAlignment::center);

    mPB = new eProgressBar(window());
    mPB->fitContent();
    mPB->setWidth(width() / 2);
    addWidget(mPB);
    mPB->align(eAlignment::center);

    mLabel = new eLabel("Waiting...", window());
    mLabel->setFontColor({255, 255, 255, 255});
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
