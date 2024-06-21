#include "einfowidget.h"

#include "emainwindow.h"

#include "../ebutton.h"

#include "widgets/eokbutton.h"

#include "elanguage.h"

eInfoWidget::eInfoWidget(eMainWindow* const window,
                         const bool narrow, const bool shrt) :
    eFramedWidget(window),
    mNarrow(narrow), mShort(shrt) {
    setType(eFrameType::message);
}

void eInfoWidget::initialize(const std::string& title) {
    const auto res = window()->resolution();
    const int ww = mNarrow ? res.centralWidgetSmallWidth() :
                             res.centralWidgetLargeWidth();
    const int hh = mShort ? res.centralWidgetSmallHeight() :
                            res.centralWidgetLargeHeight();
    resize(ww, hh);
    align(eAlignment::center);

    mTitleLabel = new eLabel(title, window());
    mTitleLabel->fitContent();
    addWidget(mTitleLabel);
    mTitleLabel->align(eAlignment::top | eAlignment::hcenter);

    mOk = new eOkButton(window());
    addWidget(mOk);
    mOk->align(eAlignment::bottom | eAlignment::right);
    const int p = padding();
    mOk->move(mOk->x() - 2*p, mOk->y() - 2*p);
}

eWidget* eInfoWidget::addCentralWidget() {
    if(mCentralWidget) return nullptr;
    mCentralWidget = new eWidget(window());
    const int p = padding();

    int h = height() - 6*p - mTitleLabel->height();
    for(const auto w : mWidgets) {
        h -= w->height() + p;
    }
    addInfoWidget(mCentralWidget, h);
    return mCentralWidget;
}

eWidget* eInfoWidget::addFramedWidget(const int height) {
    const int p = padding();

    const auto wid = new eFramedWidget(window());
    wid->setType(eFrameType::inner);
    addInfoWidget(wid, height);

    const auto wwid = new eWidget(window());
    wid->addWidget(wwid);
    wwid->resize(wid->width() - 2*p, wid->height() - 2*p);
    wwid->move(p, p);

    return wwid;
}

eWidget* eInfoWidget::addRegularWidget(const int height) {
    const auto wid = new eWidget(window());
    addInfoWidget(wid, height);
    return wid;
}

void eInfoWidget::addText(const std::string& text) {
    const auto wid = new eLabel(window());
    wid->setSmallFontSize();
    wid->setWrapWidth(widgetWidth());
    wid->setText(text);
    wid->fitContent();
    addInfoWidget(wid);
}

void eInfoWidget::addInfoWidget(eWidget* const w) {
    addInfoWidget(w, w->height());
}

void eInfoWidget::addInfoWidget(eWidget* const w, const int height) {
    const int p = padding();

    const auto cw = centralWidget();
    if(cw) {
        cw->setHeight(cw->height() - height - p);
    }

    int y = mTitleLabel->y() + mTitleLabel->height();

    for(const auto w : mWidgets) {
        y += w->height() + p;
    }

    mWidgets.push_back(w);
    addWidget(w);
    w->resize(widgetWidth(), height);
    w->move(2*p, y);
}

int eInfoWidget::widgetWidth() const {
    const int p = padding();
    return width() - 4*p;
}

void eInfoWidget::setCloseAction(const eAction& closeAction) {
    mOk->setPressAction(closeAction);
}

eWidget* eInfoWidget::centralWidget() const {
    return mCentralWidget;
}

int eInfoWidget::remainingHeight() const {
    const int p = padding();
    int h = height() - 6*p - mTitleLabel->height();
    for(const auto w : mWidgets) {
        h -= w->height() + p;
    }
    return h;
}

bool eInfoWidget::mousePressEvent(const eMouseEvent& e) {
    return e.button() == eMouseButton::left;
}
