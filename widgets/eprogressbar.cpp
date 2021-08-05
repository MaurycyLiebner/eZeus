#include "eprogressbar.h"

eProgressBar::eProgressBar(eMainWindow* const window) :
    eFramedWidget(window) {

}

void eProgressBar::setRange(const int min, const int max) {
    mMin = min;
    mMax = max;
}

void eProgressBar::setValue(const int v) {
    mValue = v;
}

void eProgressBar::sizeHint2(int& w, int& h) {
    w = 10*padding();
    h = 2*padding();
}

void eProgressBar::paintEvent(ePainter& p) {
    eFramedWidget::paintEvent(p);
    const double per = double(mValue - mMin)/(mMax - mMin);
    const int pa = padding();
    const int w = per*(width() - 2*pa);
    const SDL_Rect rect{pa, pa, w, height() - 2*pa};
    p.fillRect(rect, {255, 255, 255, 255});
}
