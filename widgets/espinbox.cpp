#include "espinbox.h"

#include "ebutton.h"

#include "textures/egametextures.h"

void eSpinBox::initialize() {
    mValueLabel = new eLabel(window());

    const auto& intrfc = eGameTextures::interface();
    const auto res = resolution();
    int iRes;
    switch(res) {
    case eRes::p2160:
    case eRes::p1440:
    case eRes::p1080:
        iRes = 2;
        break;
    case eRes::p720:
        iRes = 1;
        break;
    case eRes::p480:
        iRes = 0;
        break;
    }
    const auto& texs = intrfc[iRes];

    const auto up = new eButton(window());
    up->setTexture(texs.fUpButton.getTexture(0));
    up->setHoverTexture(texs.fUpButton.getTexture(1));
    up->setPressedTexture(texs.fUpButton.getTexture(2));
    up->fitContent();
    up->setPressAction([this]() {
        setValue(mValue + mIncrement);
    });

    const auto down = new eButton(window());
    down->setTexture(texs.fDownButton.getTexture(0));
    down->setHoverTexture(texs.fDownButton.getTexture(1));
    down->setPressedTexture(texs.fDownButton.getTexture(2));
    down->fitContent();
    up->setPressAction([this]() {
        setValue(mValue - mIncrement);
    });

    mValueLabel->setWidth(3*down->width());
    mValueLabel->setHeight(down->height());
    setValue(0);

    addWidget(mValueLabel);
    addWidget(up);
    addWidget(down);
    stackHorizontally();
    fitContent();
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
    mValueLabel->setText(std::to_string(v));
}
