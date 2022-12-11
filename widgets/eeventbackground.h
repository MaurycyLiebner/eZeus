#ifndef EEVENTBACKGROUND_H
#define EEVENTBACKGROUND_H

#include "ewidget.h"

class eEventBackground : public eWidget {
public:
    using eWidget::eWidget;

    void initialize(eWidget* const parent,
                    eWidget* const child,
                    const bool closable,
                    const eAction& closeFunc);
protected:
    void paintEvent(ePainter& p);
    bool keyPressEvent(const eKeyPressEvent& e);
    bool mousePressEvent(const eMouseEvent& e);
private:
    void close();

    bool mClosable = false;
    eAction mCloseFunc;
};

#endif // EEVENTBACKGROUND_H
