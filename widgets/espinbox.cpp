#include "espinbox.h"

#include "ebutton.h"

#include "textures/egametextures.h"

#include "eupbutton.h"
#include "edownbutton.h"

#include <algorithm>

void eSpinBox::initialize(const eAction& changed) {
    mValueLabel = new eLabel(window());

    const auto up = new eUpButton(window());
    up->setPressAction([this, changed]() {
        setValue(mValue + mIncrement);
        if(changed) changed();
    });

    const auto down = new eDownButton(window());
    down->setPressAction([this, changed]() {
        setValue(mValue - mIncrement);
        if(changed) changed();
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
