#include "edatebutton.h"

#include "edatewidget.h"
#include "emainwindow.h"

void eDateButton::initialize() {
    setUnderline(false);
    setPressAction([this]() {
        const auto dw = new eDateWidget(window());
        dw->initialize([this](const eDate& d) {
            setDate(d);
        }, false);
        dw->setDate(mDate);
        window()->execDialog(dw);
        dw->align(eAlignment::center);
    });
    setDate(eDate(31, eMonth::september, -9999));
    fitContent();
}

void eDateButton::setDate(const eDate& d) {
    setText(d.shortString());
    mDate = d;
}
