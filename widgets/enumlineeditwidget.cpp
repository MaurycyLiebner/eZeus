#include "enumlineeditwidget.h"

#include "enumlineedit.h"
#include "eokbutton.h"

void eNumLineEditWidget::initialize(const eValueAction& a,
                                    const bool actOnChange,
                                    const int min,
                                    const int max) {
    setType(eFrameType::message);

    mEdit = new eNumLineEdit(window());
    mEdit->setRenderBg(true);
    mEdit->setRange(min, max);
    mEdit->setValue(max);
    mEdit->fitContent();
    if(actOnChange) {
        mEdit->setChangeAction([this, a]() {
            if(a) a(value());
        });
    }

    addWidget(mEdit);

    const int p = padding();
    mEdit->move(2*p, 2*p);

    fitContent();

    if(!actOnChange) {
        setWidth(width() + 2*p);
        setHeight(height() + 2*p);
        const auto ok = new eOkButton(window());
        ok->setPressAction([this, a]() {
            if(a) a(value());
            deleteLater();
        });
        addWidget(ok);
        ok->align(eAlignment::right | eAlignment::bottom);
        ok->setX(ok->x() - 1.5*p);
        ok->setY(ok->y() - 1.5*p);
    }

    mEdit->grabKeyboard();
}

int eNumLineEditWidget::value() const {
    return mEdit->clampedValue();
}

void eNumLineEditWidget::setValue(const int v) {
    mEdit->setValue(v);
}
