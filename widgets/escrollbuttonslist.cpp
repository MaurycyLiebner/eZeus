#include "escrollbuttonslist.h"

#include "escrollwidgetcomplete.h"

#include "elanguage.h"
#include "eframedbutton.h"

void eScrollButtonsList::initialize() {
    setType(eFrameType::message);

    const int p = padding();

    const auto addStr = eLanguage::text("add");
    mNewButton = new eFramedButton(addStr, window());
    if(mSmallSize) {
        mNewButton->setSmallFontSize();
        mNewButton->setSmallPadding();
    }
    mNewButton->fitContent();
    mNewButton->setY(height() - 2*p - mNewButton->height());
    mNewButton->setX(2*p);
    mNewButton->setUnderline(false);

    const auto scrollCont = new eScrollWidgetComplete(window());
    addWidget(scrollCont);
    const int swcHeight = height() - 4*p - mNewButton->height() - p;
    scrollCont->resize(width() - 4*p, swcHeight);
    scrollCont->setY(2*p);
    scrollCont->setX(2*p);
    scrollCont->initialize();
    const int swwidth = scrollCont->listWidth();
    mNewButton->setWidth(swwidth);

    mSA = new eWidget(window());
    mSA->resize(swwidth - 2*p, 0);
    mBLW = new eButtonsListWidget(window());
    mBLW->setRenderButtonBg(true);
    mBLW->resize(swwidth - 2*p, 0);
    mBLW->initialize(false);
    mSA->addWidget(mBLW);
    mSA->setNoPadding();
    mSA->fitContent();
    scrollCont->setScrollArea(mSA);

    addWidget(mNewButton);
}

void eScrollButtonsList::setButtonPressEvent(const eButtonPressedEvent& e) {
    mBLW->setButtonPressEvent([e, this](const int id) {
        if(e) e(id);
        updateWidgetSize();
    });
}

void eScrollButtonsList::setButtonCreateEvent(const eButtonCreateEvent& e) {
    mNewButton->setPressAction([e, this]() {
        if(e) e();
        updateWidgetSize();
    });
}

void eScrollButtonsList::setButtonRemoveEvent(const eButtonRemoveEvent& e) {
    mBLW->setButtonRemoveEvent([e, this](const int id) {
        if(e) e(id);
        updateWidgetSize();
    });
}

void eScrollButtonsList::setText(const int id, const std::string& text) {
    mBLW->setText(id, text);
}

int eScrollButtonsList::addButton(const std::string& text) {
    const int r = mBLW->addButton(text);
    updateWidgetSize();
    return r;
}

void eScrollButtonsList::removeButton(const int id) {
    mBLW->removeButton(id);
    updateWidgetSize();
}

void eScrollButtonsList::setSmallSize(const bool b) {
    mSmallSize = b;
}

void eScrollButtonsList::updateWidgetSize() {
    mBLW->fitHeight();
    mSA->fitHeight();
}
