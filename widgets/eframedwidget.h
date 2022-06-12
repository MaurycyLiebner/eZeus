#ifndef EFRAMEDWIDGET_H
#define EFRAMEDWIDGET_H

#include "ewidget.h"

enum class eFrameType {
    outer, message, inner
};

class eFramedWidget : public eWidget {
public:
    using eWidget::eWidget;

    void setType(const eFrameType type);
protected:
    void paintEvent(ePainter& p);
private:
    eFrameType mType = eFrameType::outer;
};

#endif // EFRAMEDWIDGET_H
