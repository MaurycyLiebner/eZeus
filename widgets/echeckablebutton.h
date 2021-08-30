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
    void setCheckedTexture(const std::shared_ptr<eTexture>& tex);
private:
    using eButton::setPressAction;
private:
    void paintEvent(ePainter& p);

    std::shared_ptr<eTexture> mCheckedTexture;
    bool mChecked = false;
};

#endif // ECHECKABLEBUTTON_H
