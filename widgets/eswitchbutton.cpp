#include "eswitchbutton.h"

eSwitchButton::eSwitchButton(eMainWindow* const window) :
    eButton(window) {
    setPressAction([this]() { switchValue(); });
}

int eSwitchButton::addValue(const std::string& v) {
    mValues.push_back(v);
    const int s = mValues.size();
    if(s == 1) switchValue();
    return s;
}

void eSwitchButton::switchValue() {
    setValue(mCurrentValue + 1);
}

void eSwitchButton::setValue(const int v) {
    const int maxVal = mValues.size();
    mCurrentValue = v % maxVal;
    setText(mValues[mCurrentValue]);
    if(mSwitchAction) mSwitchAction(mCurrentValue);
}

void eSwitchButton::setSwitchAction(const eSwitchAction& a) {
    mSwitchAction = a;
}
