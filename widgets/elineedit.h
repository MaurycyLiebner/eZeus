#ifndef ELINEEDIT_H
#define ELINEEDIT_H

#include "elabel.h"

class eLineEdit : public eLabel {
public:
    eLineEdit(eMainWindow* const window);

    bool keyPressEvent(const eKeyPressEvent& e);
    void paintEvent(ePainter& p);
};

#endif // ELINEEDIT_H
