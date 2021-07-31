#include "einfowidget.h"

#include "emainwindow.h"

eInfoWidget::eInfoWidget(eMainWindow* const window) :
    eWidget(window) {

}

void eInfoWidget::initialize() {
    const auto res = window()->resolution();
    resize(eResolution::centralWidgetWidth(res),
           eResolution::centralWidgetHeight(res));
    align(eAlignment::center);
}

void eInfoWidget::paintEvent(ePainter& p) {
    p.fillRect(rect(), {255, 255, 255, 255});
}
