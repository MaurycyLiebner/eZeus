#ifndef ELINEWIDGET_H
#define ELINEWIDGET_H

#include "ewidget.h"

class eLineWidget : public eWidget {
public:
    using eWidget::eWidget;

    void sizeHint(int& w, int& h);
protected:
    void paintEvent(ePainter& p);
};

#endif // ELINEWIDGET_H
