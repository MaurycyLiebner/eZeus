#ifndef ELINEEDIT_H
#define ELINEEDIT_H

#include "eframedlabel.h"

class eLineEdit : public eFramedLabel {
public:
    eLineEdit(eMainWindow* const window);

    void setChangeAction(const eAction a);

    void setRenderBg(const bool r);
protected:
    bool mouseMoveEvent(const eMouseEvent& e);
    bool mouseEnterEvent(const eMouseEvent& e);
    bool mouseLeaveEvent(const eMouseEvent& e);
    bool keyPressEvent(const eKeyPressEvent& e);
    void paintEvent(ePainter& p);
private:
    bool mHovered = false;
    bool mRenderBg = false;
    eAction mChangeAction;
    int mTime = 0;
};

#endif // ELINEEDIT_H
