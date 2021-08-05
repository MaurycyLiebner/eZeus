#ifndef EFRAMEDLABEL_H
#define EFRAMEDLABEL_H

#include "eframedwidget.h"
#include "efonts.h"
#include "elabelbase.h"

class eFramedLabel : public eFramedWidget, public eLabelBase {
public:
    eFramedLabel(eMainWindow* const window);
    eFramedLabel(const std::string& text,
                 eMainWindow* const window);
protected:
    void sizeHint2(int& w, int& h);
    void paintEvent(ePainter& p);
};

#endif // EFRAMEDLABEL_H
