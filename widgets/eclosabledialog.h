#ifndef ECLOSABLEDIALOG_H
#define ECLOSABLEDIALOG_H

#include "eframedwidget.h"

class eClosableDialog : public eFramedWidget {
public:
    using eFramedWidget::eFramedWidget;
protected:
    bool keyPressEvent(const eKeyPressEvent& e);
    bool mousePressEvent(const eMouseEvent& e);
};

#endif // ECLOSABLEDIALOG_H
