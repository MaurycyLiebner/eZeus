#ifndef EFRAMEDWIDGET_H
#define EFRAMEDWIDGET_H

#include "ewidget.h"

enum class eFrameType {
    outer, message, inner
};

class eFramedWidget : public eWidget {
public:
    using eWidget::eWidget;
protected:
    void sizeHint(int& w, int& h) final;
    virtual void sizeHint2(int& w, int& h) {
        eWidget::sizeHint(w, h);
    }

    void setType(const eFrameType type);

    void paintEvent(ePainter& p);
private:
    void iResAndDim(int& iRes, int& dim) const;

    eFrameType mType = eFrameType::outer;
};

#endif // EFRAMEDWIDGET_H
