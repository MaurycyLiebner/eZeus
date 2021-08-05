#ifndef EFRAMEDWIDGET_H
#define EFRAMEDWIDGET_H

#include "ewidget.h"

class eFramedWidget : public eWidget {
public:
    using eWidget::eWidget;
protected:
    void sizeHint(int& w, int& h) final;
    virtual void sizeHint2(int& w, int& h) = 0;

    void paintEvent(ePainter& p);
private:
    void iResAndDim(int& iRes, int& dim) const;
};

#endif // EFRAMEDWIDGET_H
