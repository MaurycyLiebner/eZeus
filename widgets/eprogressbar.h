#ifndef EPROGRESSBAR_H
#define EPROGRESSBAR_H

#include "eframedwidget.h"

class eProgressBar : public eFramedWidget {
public:
    eProgressBar(eMainWindow* const window);

    int value() const { return mValue; }

    void setRange(const int min, const int max);
    void setValue(const int v);
protected:
    void sizeHint(int& w, int& h);

    void paintEvent(ePainter& p);
private:
    int mMin = 0;
    int mMax = 100;
    int mValue = 0;
};

#endif // EPROGRESSBAR_H
