#include "escrollwidgetcomplete.h"

#include "escrollwidget.h"
#include "escrollbar.h"
#include "eframedwidget.h"

void eScrollWidgetComplete::initialize() {
    mSB = new eScrollBar(window());
    mSB->initialize(height());
    addWidget(mSB);

    const int p = padding();

    const int swwidth = listWidth();

    const auto swww = new eFramedWidget(window());
    swww->setNoPadding();
    swww->setType(eFrameType::inner);
    mSW = new eScrollWidget(window());
    swww->addWidget(mSW);
    mSW->resize(swwidth - 2*p, height() - 2*p);
    mSW->move(p, p);
    swww->resize(swwidth, height());
    mSB->setScrollWidget(mSW);
    addWidget(swww);

    mSB->align(eAlignment::right);
}

void eScrollWidgetComplete::setScrollArea(eWidget* const widget) {
    mSW->setScrollArea(widget);
}

int eScrollWidgetComplete::listWidth() const {
    const int p = padding();
    return width() - mSB->width() - p;
}
