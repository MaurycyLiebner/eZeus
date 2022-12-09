#include "eeventbackground.h"

void eEventBackground::initialize(eWidget* const parent,
                                  eWidget* const child) {
    parent->removeWidget(child);
    addWidget(child);
    parent->addWidget(this);
    resize(parent->width(), parent->height());
}

void eEventBackground::paintEvent(ePainter& p) {
    (void)p;
    if(children().size() == 0) deleteLater();
}

bool eEventBackground::keyPressEvent(const eKeyPressEvent& e) {
    const auto k = e.key();
    if(k == SDL_SCANCODE_ESCAPE) {
        deleteLater();
    }
    return true;
}

bool eEventBackground::mousePressEvent(const eMouseEvent& e) {
    const auto b = e.button();
    if(b == eMouseButton::right) {
        deleteLater();
    }
    return true;
}
