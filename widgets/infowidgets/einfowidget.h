#ifndef EINFOWIDGET_H
#define EINFOWIDGET_H

#include "../ewidget.h"

class eInfoWidget : public eWidget {
public:
    eInfoWidget(eMainWindow* const window);

    void initialize();
protected:
    void paintEvent(ePainter& p);
};

#endif // EINFOWIDGET_H
