#include "eeventbackground.h"

void eEventBackground::initialize(eWidget* const parent,
                                  eWidget* const child,
                                  const bool closable,
                                  const eAction &closeFunc) {
    parent->removeWidget(child);
    addWidget(child);
    parent->addWidget(this);
    resize(parent->width(), parent->height());
    mClosable = closable;
    mCloseFunc = closeFunc;
}

void eEventBackground::paintEvent(ePainter& p) {
    (void)p;
    if(children().size() == 0) deleteLater();
}

bool eEventBackground::keyPressEvent(const eKeyPressEvent& e) {
    if(!mClosable) return true;
    const auto k = e.key();
    if(k == SDL_SCANCODE_ESCAPE) {
        close();
    }
    return true;
}

bool eEventBackground::mousePressEvent(const eMouseEvent& e) {
    if(!mClosable) return true;
    const auto b = e.button();
    if(b == eMouseButton::right) {
        close();
    }
    return true;
}

void eEventBackground::close() {
    if(mCloseFunc) mCloseFunc();
    deleteLater();
}
