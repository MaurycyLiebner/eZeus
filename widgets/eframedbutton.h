#ifndef EFRAMEDBUTTON_H
#define EFRAMEDBUTTON_H

#include "ebutton.h"

class eFramedButton : public eButton {
public:
    using eButton::eButton;

    void setRenderBg(const bool r) { mRenderBg = r; }
protected:
    void paintEvent(ePainter& p);
private:
    void renderBg(ePainter& p);

    bool mRenderBg = false;
};

#endif // EFRAMEDBUTTON_H
