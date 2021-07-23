#include "emainmenu.h"

#include "ebutton.h"

eMainMenu::eMainMenu(SDL_Renderer* const renderer) :
    eWidget(renderer) {}

void eMainMenu::initialize() {
    const auto buttons = new eWidget(renderer());
    addWidget(buttons);
    buttons->resize(500, 500);
    buttons->align(eAlignment::center);

    const auto b1 = new eButton(renderer());
    buttons->addWidget(b1);
    b1->setText("New Game");
    b1->resize(200, 50);
    b1->align(eAlignment::top | eAlignment::hcenter);

    const auto b2 = new eButton(renderer());
    buttons->addWidget(b2);
    b2->setText("Load Game");
    b2->resize(300, 50);
    b2->align(eAlignment::vcenter | eAlignment::hcenter);

    const auto b3 = new eButton(renderer());
    buttons->addWidget(b3);
    b3->setText("Quit");
    b3->resize(150, 50);
    b3->align(eAlignment::bottom | eAlignment::hcenter);
}

void eMainMenu::paintEvent(ePainter& p) {
    if(mPressed) {
        if(mHover) {
            p.drawRect(rect(), {255, 255, 0, 255}, 5);
        } else {
            p.drawRect(rect(), {255, 0, 255, 255}, 5);
        }
    } else {
        if(mHover) {
            p.drawRect(rect(), {0, 255, 0, 255}, 5);
        } else {
            p.drawRect(rect(), {255, 0, 0, 255}, 5);
        }
    }
}

bool eMainMenu::mousePressEvent(const eMouseEvent& e) {
    (void)e;
    mPressed = true;
    return true;
}

bool eMainMenu::mouseReleaseEvent(const eMouseEvent& e) {
    (void)e;
    mPressed = false;
    return true;
}

bool eMainMenu::mouseMoveEvent(const eMouseEvent& e) {
    (void)e;
    return true;
}

bool eMainMenu::mouseEnterEvent(const eMouseEvent& e) {
    (void)e;
    mHover = true;
    return true;
}

bool eMainMenu::mouseLeaveEvent(const eMouseEvent& e) {
    (void)e;
    mHover = false;
    return true;
}
