#ifndef EFRAMEDBUTTON_H
#define EFRAMEDBUTTON_H

#include "ebutton.h"

class eFramedButton : public eButton {
public:
    using eButton::eButton;

protected:
    void paintEvent(ePainter& p);
};

#endif // EFRAMEDBUTTON_H
