#ifndef EBUTTON_H
#define EBUTTON_H

#include "elabel.h"
#include "efonts.h"

class eButton : public eLabel {
public:
    eButton(eMainWindow* const window);

    void setPressAction(const eAction& a);

    void setHoverTexture(const eTexture& tex);
    void setPressedTexture(const eTexture& tex);
protected:
    void sizeHint(int& w, int& h);
    void paintEvent(ePainter& p);

    bool mousePressEvent(const eMouseEvent& e);
    bool mouseReleaseEvent(const eMouseEvent& e);
    bool mouseMoveEvent(const eMouseEvent& e);
    bool mouseEnterEvent(const eMouseEvent& e);
    bool mouseLeaveEvent(const eMouseEvent& e);
private:
    eTexture mTexture;
    eTexture mHoverTexture;
    eTexture mPressedTexture;

    eAction mPressAction;

    bool mPressed = false;
    bool mHover = false;
};

#endif // EBUTTON_H
