#include "eloadingwidget.h"

#include "emainwindow.h"
#include "textures/egametextures.h"
#include "textures/einterfacetextures.h"

eLoadingWidget::eLoadingWidget(const int size,
                               const eLoader& loader,
                               eMainWindow* const window,
                               const bool useTextures) :
    eWidget(window), mUseTextures(useTextures),
    mSize(size), mLoader(loader) {
}

void eLoadingWidget::initialize() {
    const auto& intrfc = eGameTextures::interface();

    const auto res = resolution();
    const int iRes = static_cast<int>(res.uiScale());
    if(mUseTextures) {
        const auto bg = new eFramedLabel(window());
        const auto& texs = intrfc[iRes];
        bg->setTexture(texs.fLoadImage);
        bg->fitContent();
        addWidget(bg);
        bg->align(eAlignment::center);
    }

    mPB = new eProgressBar(window());
    mPB->fitContent();
    mPB->setWidth(width() / 4);
    addWidget(mPB);
    mPB->align(eAlignment::center);

    if(mUseTextures) {
        const auto label = new eFramedLabel("Waiting...", window());
        mLabelW = label;
        mLabel = label;
        mLabel->setFontColor({255, 255, 255, 255});
    } else {
        const auto label = new eLabel("Waiting...", window());
        mLabelW = label;
        mLabel = label;
    }
    mLabelW->fitContent();
    addWidget(mLabelW);
    mLabelW->align(eAlignment::hcenter);
    mLabelW->setY(mPB->y() + 2*mLabelW->height());

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
        mLabelW->fitContent();
        mLabelW->align(eAlignment::hcenter);
    }
    eWidget::paintEvent(p);
}
