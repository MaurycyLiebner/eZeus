#ifndef ELABEL_H
#define ELABEL_H

#include "ewidget.h"
#include "efonts.h"
#include "elabelbase.h"

class eLabel : public eWidget, public eLabelBase {
public:
    eLabel(eMainWindow* const window);
    eLabel(const std::string& text,
           eMainWindow* const window);

    bool setTinyFontSize();
    bool setVerySmallFontSize();
    bool setSmallFontSize();
    bool setHugeFontSize();
protected:
    void sizeHint(int& w, int& h);
    void paintEvent(ePainter& p);
};

#endif // ELABEL_H
