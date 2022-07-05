#include "elinewidget.h"

#include "efontcolor.h"

void eLineWidget::sizeHint(int& w, int& h) {
    const auto res = resolution();
    const int m = res.multiplier();
    w = 2*m;
    h = 2*m;
}

void eLineWidget::paintEvent(ePainter& p) {
    SDL_Color col1;
    SDL_Color col2;
    eFontColorHelpers::colors(eFontColor::light, col1, col2);

    p.fillRect(SDL_Rect{0, 0, width(), height()}, col2);
    const int hh = height()/2;
    p.fillRect(SDL_Rect{0, hh, width(), hh}, col1);
}
