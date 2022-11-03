#ifndef EFLATBUTTON_H
#define EFLATBUTTON_H

#include "ebuttonbase.h"

class eFlatButton : public eButtonBase {
public:
    using eButtonBase::eButtonBase;
protected:
    void paintEvent(ePainter& p);
};

#endif // EFLATBUTTON_H
