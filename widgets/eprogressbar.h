#ifndef EPROGRESSBAR_H
#define EPROGRESSBAR_H

#include "ewidget.h"

class eProgressBar : public eWidget {
public:
    eProgressBar(eMainWindow* const window);

    void setRange(const int min, const int max);
    void setValue(const int v);
protected:
    void sizeHint(int& w, int& h);

    void paintEvent(ePainter& p);
private:
    int mMin;
    int mMax;
    int mValue;
};

#endif // EPROGRESSBAR_H
