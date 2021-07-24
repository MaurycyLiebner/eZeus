#include "emainmenu.h"

#include "ebutton.h"

eMainMenu::eMainMenu(eMainWindow* const window) :
    eWidget(window) {}

void eMainMenu::initialize(const eAction& newGameA,
                           const eAction& loadGameA,
                           const eAction& settingsA,
                           const eAction& quitA) {
    const auto buttons = new eWidget(window());
    addWidget(buttons);

    const auto res = resolution();
    const int cww = eResolution::centralWidgetWidth(res);
    const int cwh = eResolution::centralWidgetHeight(res);
    buttons->resize(cww, cwh);

    buttons->align(eAlignment::center);

    {
        const auto b1 = new eButton(window());
        b1->setPressAction(newGameA);
        buttons->addWidget(b1);
        b1->setText("New Game");
        b1->fitContent();
        b1->align(eAlignment::hcenter);
    }

    {
        const auto b2 = new eButton(window());
        b2->setPressAction(loadGameA);
        buttons->addWidget(b2);
        b2->setText("Load Game");
        b2->fitContent();
        b2->align(eAlignment::hcenter);
    }

    {
        const auto b3 = new eButton(window());
        b3->setPressAction(settingsA);
        buttons->addWidget(b3);
        b3->setText("Settings");
        b3->fitContent();
        b3->align(eAlignment::hcenter);
    }

    {
        const auto b4 = new eButton(window());
        b4->setPressAction(quitA);
        buttons->addWidget(b4);
        b4->setText("Quit");
        b4->fitContent();
        b4->align(eAlignment::hcenter);
    }

    buttons->layoutVertically();
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
