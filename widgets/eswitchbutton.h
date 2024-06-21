#ifndef ESWITCHBUTTON_H
#define ESWITCHBUTTON_H

#include "eframedbutton.h"

class eSwitchButton : public eFramedButton {
public:
    eSwitchButton(eMainWindow* const window);

    int addValue(const std::string& v);
    int currentValue() const { return mCurrentValue; }

    void switchValue();
    void setValue(const int v);

    using eSwitchAction = std::function<void(int)>;
    void setSwitchAction(const eSwitchAction& a);

    void fitValialbeContent();
private:
    int mCurrentValue = 0;
    std::vector<std::string> mValues;

    eSwitchAction mSwitchAction;
};

#endif // ESWITCHBUTTON_H
