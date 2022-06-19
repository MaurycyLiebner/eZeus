#include "einfowidget.h"

#include "emainwindow.h"

#include "../ebutton.h"

#include "widgets/eokbutton.h"

#include "elanguage.h"

eInfoWidget::eInfoWidget(eMainWindow* const window) :
    eFramedWidget(window) {
    setType(eFrameType::message);
}

void eInfoWidget::initialize(const std::string& title) {
    const auto res = window()->resolution();
    resize(res.centralWidgetWidth(),
           res.centralWidgetHeight());
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
    const int h = height() - 7*p - titleLabel->height();
    mCentralWidget->resize(w, h);

    mOk = new eOkButton(window());
    addWidget(mOk);
    mOk->align(eAlignment::bottom | eAlignment::right);
    mOk->move(mOk->x() - 2*p, mOk->y() - 2*p);
}

void eInfoWidget::setCloseAction(const eAction& closeAction) {
    mOk->setPressAction(closeAction);
}

eWidget* eInfoWidget::centralWidget() const {
    return mCentralWidget;
}
