#include "echeckbox.h"

eCheckBox::eCheckBox(eMainWindow* const window) :
    eWidget(window) {

}

void eCheckBox::setChecked(const bool c) {
    mChecked = c;
}

void eCheckBox::setCheckAction(const eCheckAction& a) {
    mAction = a;
}

void eCheckBox::sizeHint(int& w, int& h) {
    const int pd = eResolution::padding(resolution());
    w = pd;
    h = pd;
}

void eCheckBox::paintEvent(ePainter& p) {
    SDL_Color col;
    if(mChecked) {
        col = {0, 0, 0, 255};
    } else {
        col = {200, 200, 200, 255};
    }
    const int pd = eResolution::padding(resolution());
    const SDL_Rect rect{pd, pd, width() - 2*pd, height() - 2*pd};
    p.fillRect(rect, col);
}

bool eCheckBox::mousePressEvent(const eMouseEvent& e) {
    (void)e;
    setChecked(!mChecked);
    if(mAction) mAction(mChecked);
    return true;
}
