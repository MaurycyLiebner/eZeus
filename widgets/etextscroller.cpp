#include "etextscroller.h"

#include "escrollwidgetcomplete.h"
#include "eframedwidget.h"
#include "elabel.h"

void eTextScroller::initialize() {
    mSW = new eScrollWidgetComplete(window());
    mSW->resize(width(), height());
    mSW->initialize();

    mScrollTextLabel = new eLabel(window());
    const int w = mSW->areaWidth();
    mScrollTextLabel->setWrapWidth(w);
    mScrollTextLabel->setWidth(w);
    mScrollTextLabel->setNoPadding();

    mSW->setScrollArea(mScrollTextLabel);

    addWidget(mSW);
    mSW->hide();

    const auto res = resolution();
    const int p = res.smallPadding();

    mBg = new eFramedWidget(window());
    mBg->setNoPadding();
    mBg->setType(eFrameType::inner);
    mBg->resize(width(), height());

    mTextLabel = new eLabel(window());
    mTextLabel->setWrapWidth(width() - 2*p);
    mBg->addWidget(mTextLabel);
    mTextLabel->move(p, p);

    addWidget(mBg);
}

void eTextScroller::setText(const std::string& text) {
    mTextLabel->setText(text);
    mTextLabel->fitContent();
    const auto res = resolution();
    const int p = res.smallPadding();
    const bool s = mTextLabel->height() > mBg->height() - 2*p;
    mBg->setVisible(!s);
    mScrollTextLabel->setText(text);
    mScrollTextLabel->fitContent();
    mSW->setVisible(s);
    mSW->scrollToTheTop();
    mSW->clampDY();
}

void eTextScroller::setTinyTextFontSize() {
    mTextLabel->setTinyFontSize();
    mScrollTextLabel->setTinyFontSize();
}

void eTextScroller::setTinyTextPadding() {
    mTextLabel->setTinyPadding();
}
