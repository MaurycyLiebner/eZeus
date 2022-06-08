#include "einfowidget.h"

#include "emainwindow.h"

#include "../ebutton.h"

#include "elanguage.h"

eInfoWidget::eInfoWidget(eMainWindow* const window) :
    eFramedWidget(window) {

}

void eInfoWidget::initialize() {
    const auto res = window()->resolution();
    resize(res.centralWidgetWidth(),
           res.centralWidgetHeight());
    align(eAlignment::center);

    mOk = new eButton(window());
    mOk->setText(eLanguage::text("ok"));
    mOk->fitContent();

    addWidget(mOk);
    mOk->align(eAlignment::bottom | eAlignment::right);
}

void eInfoWidget::setCloseAction(const eAction& closeAction) {
    mOk->setPressAction(closeAction);
}

SDL_Rect eInfoWidget::centralWidgetRect() const {
    const int p = padding();
    return {p, p, width() - 2*p, height() - 4*p};
}
