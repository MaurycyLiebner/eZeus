#include "evlayout.h"

eVLayout::eVLayout() {

}

void eVLayout::layoutWidgets(const SDL_Rect& rect, const eWidgets& ws) const {
    const int spaces = ws.size() + 1;
    int wsHeight = 0;
    for(const auto w : ws) {
        wsHeight += w->height();
    }
    const int space = (rect.h - wsHeight)/spaces;
    int y = space;
    for(const auto w : ws) {
        w->setY(y);
        y += w->height() + space;
    }
}
