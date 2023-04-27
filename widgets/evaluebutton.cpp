#include "evaluebutton.h"

#include "enumlineeditwidget.h"
#include "emainwindow.h"

void eValueButton::initialize(const int min, const int max) {
    setUnderline(false);
    setPressAction([this, min, max]() {
        const auto dw = new eNumLineEditWidget(window());
        dw->initialize([this](const int v) {
            setValue(v);
            if(mValueChangeAction) mValueChangeAction(v);
        }, false, min, max);
        dw->setValue(mValue);
        window()->execDialog(dw);
        dw->align(eAlignment::center);
    });
    setValue(max);
    fitContent();
}

void eValueButton::setValueChangeAction(const eValueChangeAction& a) {
    mValueChangeAction = a;
}

void eValueButton::setValue(const int v) {
    setText(std::to_string(v));
    mValue = v;
}
