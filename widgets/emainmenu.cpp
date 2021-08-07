#include "emainmenu.h"

#include "ebutton.h"

#include "eframedwidget.h"
#include "textures/egametextures.h"

eMainMenu::eMainMenu(eMainWindow* const window) :
    eLabel(window) {}

void addButton(const std::string& text,
               const eAction& a,
               eWidget* const buttons,
               eMainWindow* const window) {
    const auto w1 = new eFramedWidget(window);
    w1->setPadding(w1->padding()/2);
    buttons->addWidget(w1);
    const auto b1 = new eButton(window);
    w1->addWidget(b1);
    b1->setPressAction(a);
    b1->setText(text);
    b1->fitContent();
    w1->fitContent();
    w1->align(eAlignment::hcenter);
    b1->align(eAlignment::center);
}

void eMainMenu::initialize(const eAction& newGameA,
                           const eAction& loadGameA,
                           const eAction& settingsA,
                           const eAction& quitA) {
    const auto& intrfc = eGameTextures::interface();
    const auto res = resolution();
    int iRes;
    switch(res) {
    case eRes::p2160:
    case eRes::p1440:
    case eRes::p1080:
        iRes = 2;
        break;
    case eRes::p720:
        iRes = 1;
        break;
    case eRes::p480:
        iRes = 0;
        break;
    }
    const auto& texs = intrfc[iRes];
    setTexture(texs.fMainMenuImage);

    const auto buttons = new eWidget(window());
    addWidget(buttons);

    const int cww = eResolution::centralWidgetWidth(res);
    const int cwh = eResolution::centralWidgetHeight(res);
    buttons->resize(cww, cwh);

    buttons->align(eAlignment::center);

    addButton("New Game", newGameA, buttons, window());
    addButton("Load Game", loadGameA, buttons, window());
    addButton("Settings", settingsA, buttons, window());
    addButton("Quit", quitA, buttons, window());

    buttons->layoutVertically();
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
