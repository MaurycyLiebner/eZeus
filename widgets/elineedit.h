#ifndef ELINEEDIT_H
#define ELINEEDIT_H

#include "elabel.h"

class eLineEdit : public eLabel {
public:
    eLineEdit(eMainWindow* const window);

    void setChangeAction(const eAction a);

    bool keyPressEvent(const eKeyPressEvent& e);
    void paintEvent(ePainter& p);
private:
    eAction mChangeAction;
    int mTime = 0;
};

#endif // ELINEEDIT_H
