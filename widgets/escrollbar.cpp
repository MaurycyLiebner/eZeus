#include "escrollbar.h"

#include "escrollwidget.h"

#include "ebasicbutton.h"

void eScrollBar::initialize(const int height) {
    const auto upTex = &eInterfaceTextures::fBigUpButton;
    const auto up = new eBasicButton(upTex, window());
    up->setPressAction([this]() {
        scrollUp();
    });

    const auto downTex = &eInterfaceTextures::fBigDownButton;
    const auto down = new eBasicButton(downTex, window());
    down->setPressAction([this]() {
        scrollDown();
    });

    setHeight(height);
    setWidth(up->width());
    addWidget(up);
    addWidget(down);
    up->align(eAlignment::top);
    down->align(eAlignment::bottom);
}

void eScrollBar::setScrollWidget(eScrollWidget* const sw) {
    mSw = sw;
}

void eScrollBar::scrollUp() {
    if(!mSw) return;
    mSw->scrollUp();
}

void eScrollBar::scrollDown() {
    if(!mSw) return;
    mSw->scrollDown();
}
