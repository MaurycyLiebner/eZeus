#include "eprogressbar.h"

eProgressBar::eProgressBar(eMainWindow* const window) :
    eWidget(window) {

}

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
    p.drawRect(rect(), {0, 0, 0, 255}, 2);
    const double per = (mValue - mMin)/(mMax - mMin);
    const int pa = padding();
    const int w = per*(width() - 2*pa);
    const SDL_Rect rect{pa, pa, w, height() - 2*pa};
    p.fillRect(rect, {0, 0, 0, 255});
}
