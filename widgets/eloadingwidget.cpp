#include "eloadingwidget.h"

#include "emainwindow.h"
#include "textures/egametextures.h"
#include "textures/einterfacetextures.h"

#include "erand.h"

eLoadingWidget::eLoadingWidget(const int size,
                               const eLoader& loader,
                               eMainWindow* const window,
                               const bool useTextures) :
    eWidget(window), mUseTextures(useTextures),
    mSize(size), mLoader(loader) {
}

void eLoadingWidget::initialize() {
    if(mUseTextures) {
        mImageLabel = new eLabel(window());
        addWidget(mImageLabel);
        setLoadImage(1);
    }

    if(mUseTextures) {
        const auto label = new eFramedLabel("Waiting...", window());
        mLabelW = label;
        mLabel = label;
        mLabel->setLightFontColor();
    } else {
        const auto label = new eLabel("Waiting...", window());
        mLabelW = label;
        mLabel = label;
    }
    mLabelW->fitContent();
    addWidget(mLabelW);
    mLabelW->align(eAlignment::hcenter);
    mLabelW->setY(2*height()/3);

    mPB = new eProgressBar(window());
    mLabelW->addWidget(mPB);
    mPB->setWidth(mLabelW->width());
    mPB->setHeight(mLabelW->height()/10);
    mPB->setY(mLabelW->height());
    mPB->align(eAlignment::hcenter);
    mPB->setRange(0, mSize);

    mPB->hide();
    mLabelW->hide();
}

void eLoadingWidget::setDoneAction(const eAction& a) {
    mDoneAction = a;
}

void eLoadingWidget::setLoadImage(const int id) {
    if(!mImageLabel) return;
    const auto& intrfc = eGameTextures::interface();
    const auto res = resolution();
    const int iRes = static_cast<int>(res.uiScale());
    const auto& texs = intrfc[iRes];
    stdsptr<eTexture> tex;
    if(id == 1) {
        tex = texs.fLoadImage1;
    } else if(id == 2) {
        tex = texs.fLoadImage2;
    } else if(id == 3) {
        tex = texs.fLoadImage3;
    } else if(id == 4) {
        tex = texs.fLoadImage4;
    } else if(id == 5) {
        tex = texs.fLoadImage5;
    } else if(id == 6) {
        tex = texs.fLoadImage6;
    } else if(id == 7) {
        tex = texs.fLoadImage7;
    } else if(id == 8) {
        tex = texs.fLoadImage8;
    } else if(id == 9) {
        tex = texs.fLoadImage9;
    } else if(id == 10) {
        tex = texs.fLoadImage10;
    } else if(id == 11) {
        tex = texs.fLoadImage11;
    } else { // 12
        tex = texs.fLoadImage12;
    }
    mImageLabel->setTexture(tex);
    mImageLabel->fitContent();
    mImageLabel->align(eAlignment::center);
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
        setLoadImage(eRand::rand() % 12 + 1);

        mPB->setWidth(mLabelW->width());
        mPB->align(eAlignment::hcenter);
    }
    eWidget::paintEvent(p);
}
