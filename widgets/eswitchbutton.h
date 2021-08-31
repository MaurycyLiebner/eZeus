#ifndef ESWITCHBUTTON_H
#define ESWITCHBUTTON_H

#include "ebutton.h"

class eSwitchButton : public eButton {
public:
    eSwitchButton(eMainWindow* const window);

    int addValue(const std::string& v);
    int currentValue() const { return mCurrentValue; }

    void switchValue();
    void setValue(const int v);

    using eSwitchAction = std::function<void(int)>;
    void setSwitchAction(const eSwitchAction& a);
private:
    int mCurrentValue = 0;
    std::vector<std::string> mValues;

    eSwitchAction mSwitchAction;
};

#endif // ESWITCHBUTTON_H
