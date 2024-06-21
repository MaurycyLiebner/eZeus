#include "eprogressbar.h"

void eProgressBar::setRange(const int min, const int max) {
    mMin = min;
    mMax = max;
}

void eProgressBar::setValue(const int v) {
    mValue = v;
}

void eProgressBar::sizeHint(int& w, int& h) {
    w = 10*padding();
    h = 2*padding();
}

void eProgressBar::paintEvent(ePainter& p) {
    const double per = double(mValue - mMin)/(mMax - mMin);
    const int w = per*width();
    const SDL_Rect rect{0, 0, w, height()};
    p.fillRect(rect, {255, 255, 255, 255});
    //p.drawRect(rect, {0, 0, 0, 255} , 2);
}
