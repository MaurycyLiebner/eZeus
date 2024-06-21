#ifndef ELINEEDIT_H
#define ELINEEDIT_H

#include "eframedlabel.h"

class eLineEdit : public eFramedLabel {
public:
    eLineEdit(eMainWindow* const window);

    void setChangeAction(const eAction a);

    void setRenderBg(const bool r);

    bool keyPressEvent(const eKeyPressEvent& e);
    void paintEvent(ePainter& p);
private:
    bool mRenderBg = false;
    eAction mChangeAction;
    int mTime = 0;
};

#endif // ELINEEDIT_H
