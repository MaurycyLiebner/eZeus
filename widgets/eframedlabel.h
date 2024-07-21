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

    void renderTargetsReset() override;
protected:
    void sizeHint(int& w, int& h) override;
    void paintEvent(ePainter& p) override;
};

#endif // EFRAMEDLABEL_H
