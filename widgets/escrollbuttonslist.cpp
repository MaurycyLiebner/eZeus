#include "escrollbuttonslist.h"

#include "escrollwidgetcomplete.h"

void eScrollButtonsList::initialize() {
    setType(eFrameType::message);

    const int p = padding();

    const auto scrollCont = new eScrollWidgetComplete(window());
    addWidget(scrollCont);
    scrollCont->resize(width() - 4*p, height() - 4*p);
    scrollCont->setY(2*p);
    scrollCont->setX(2*p);
    scrollCont->initialize();
    const int swwidth = scrollCont->listWidth();

    mSA = new eWidget(window());
    mSA->resize(swwidth, 0);
    mBLW = new eButtonsListWidget(window());
    mBLW->resize(swwidth - 4*p, 0);
    mBLW->initialize();
    mBLW->move(2*p, 2*p);
    mSA->addWidget(mBLW);
    mSA->fitContent();
    scrollCont->setScrollArea(mSA);
}

void eScrollButtonsList::setButtonPressEvent(const eButtonPressedEvent& e) {
    mBLW->setButtonPressEvent([e, this](const int id) {
        if(e) e(id);
        updateWidgetSize();
    });
}

void eScrollButtonsList::setButtonCreateEvent(const eButtonCreateEvent& e) {
    mBLW->setButtonCreateEvent([e, this]() {
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

void eScrollButtonsList::updateWidgetSize() {
    mBLW->fitContent();
    mSA->fitContent();
}
