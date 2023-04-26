#include "edatebutton.h"

#include "edatewidget.h"
#include "emainwindow.h"

void eDateButton::initialize() {
    setUnderline(false);
    setPressAction([this]() {
        const auto dw = new eDateWidget(window());
        dw->initialize([this](const eDate& d) {
            setDate(d);
            if(mDateChangeAction) mDateChangeAction(d);
        }, false);
        dw->setDate(mDate);
        window()->execDialog(dw);
        dw->align(eAlignment::center);
    });
    setDate(eDate(20, eMonth::june, -2000));
    fitContent();
}

void eDateButton::setDateChangeAction(const eDateChangeAction& a) {
    mDateChangeAction = a;
}

void eDateButton::setDate(const eDate& d) {
    setText(d.shortString());
    mDate = d;
}
