#include "elinewidget.h"

#include "efontcolor.h"

void eLineWidget::sizeHint(int& w, int& h) {
    const auto res = resolution();
    const double m = res.multiplier();
    w = 2*m;
    h = 2*m;
}

void eLineWidget::paintEvent(ePainter& p) {
    const SDL_Color col1{132, 170, 197, 255};
    const SDL_Color col2{0, 65, 99, 255};

    p.fillRect(SDL_Rect{0, 0, width(), height()}, col1);
    const int hh = height()/2;
    p.fillRect(SDL_Rect{0, hh, width(), hh}, col2);
}
