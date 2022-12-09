#ifndef EEVENTBACKGROUND_H
#define EEVENTBACKGROUND_H

#include "ewidget.h"

class eEventBackground : public eWidget {
public:
    using eWidget::eWidget;

    void initialize(eWidget* const parent,
                    eWidget* const child);
protected:
    void paintEvent(ePainter& p);
    bool keyPressEvent(const eKeyPressEvent& e);
    bool mousePressEvent(const eMouseEvent& e);
};

#endif // EEVENTBACKGROUND_H
