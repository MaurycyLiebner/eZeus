#ifndef ECHECKABLEBUTTON_H
#define ECHECKABLEBUTTON_H

#include "ebutton.h"

using eCheckAction = std::function<void(bool)>;

class eCheckableButton : public eButton {
public:
    eCheckableButton(eMainWindow* const window);

    bool checked() const { return mChecked; }

    void setCheckAction(const eCheckAction& a);

    void setChecked(const bool c);
private:
    using eButton::setPressAction;
private:
    void paintEvent(ePainter& p);

    bool mChecked = false;
};

#endif // ECHECKABLEBUTTON_H