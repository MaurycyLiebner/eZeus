#include "espinbox.h"

#include "ebutton.h"

#include "textures/egametextures.h"

#include "eupbutton.h"
#include "edownbutton.h"

void eSpinBox::initialize() {
    mValueLabel = new eLabel(window());

    const auto up = new eUpButton(window());
    up->setPressAction([this]() {
        setValue(mValue + mIncrement);
    });

    const auto down = new eDownButton(window());
    down->setPressAction([this]() {
        setValue(mValue - mIncrement);
    });

    mValueLabel->setWidth(1.5*down->width());
    mValueLabel->setHeight(down->height());
    setValue(0);

    addWidget(mValueLabel);
    addWidget(up);
    addWidget(down);
    stackHorizontally();

    mValueLabel->align(eAlignment::vcenter);
    up->align(eAlignment::vcenter);
    down->align(eAlignment::vcenter);
}

void eSpinBox::setRange(const int min, const int max) {
    mMinValue = min;
    mMaxValue = max;
    setValue(mValue);
}

void eSpinBox::setIncrement(const int i) {
    mIncrement = i;
}

void eSpinBox::setValue(const int v) {
    mValue = std::clamp(v, mMinValue, mMaxValue);
    mValueLabel->setText(std::to_string(mValue));
}
