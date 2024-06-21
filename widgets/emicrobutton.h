#ifndef EMICROBUTTON_H
#define EMICROBUTTON_H

#include "ebuttonbase.h"

class eMicroButton : public eButtonBase {
public:
    using eButtonBase::eButtonBase;

    void sizeHint(int& w, int& h) override;
protected:
    void paintEvent(ePainter& p) override;
};

#endif // EMICROBUTTON_H
