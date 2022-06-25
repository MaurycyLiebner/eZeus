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

    const auto titleLabel = new eLabel(title, window());
    titleLabel->fitContent();
    addWidget(titleLabel);
    titleLabel->align(eAlignment::top | eAlignment::hcenter);

    mCentralWidget = new eWidget(window());
    addWidget(mCentralWidget);
    const int p = padding();
    const int y = titleLabel->height() + titleLabel->y();
    mCentralWidget->move(2*p, y);
    const int w = width() - 4*p;
    const int h = height() - 6*p - titleLabel->height();
    mCentralWidget->resize(w, h);

    mOk = new eOkButton(window());
    addWidget(mOk);
    mOk->align(eAlignment::bottom | eAlignment::right);
    mOk->move(mOk->x() - 2*p, mOk->y() - 2*p);
}

eWidget* eInfoWidget::addFramedWidget(const int height) {
    const auto cw = centralWidget();
    const auto p = padding();
    cw->setHeight(cw->height() - height - p);

    const auto wid = new eFramedWidget(window());
    wid->setType(eFrameType::inner);
    addWidget(wid);
    wid->resize(cw->width(), height);
    wid->move(cw->x(), cw->y() + cw->height() + p);

    const auto wwid = new eWidget(window());
    wid->addWidget(wwid);
    wwid->resize(wid->width() - 2*p, wid->height() - 2*p);
    wwid->move(p, p);

    return wwid;
}

void eInfoWidget::setCloseAction(const eAction& closeAction) {
    mOk->setPressAction(closeAction);
}

eWidget* eInfoWidget::centralWidget() const {
    return mCentralWidget;
}
