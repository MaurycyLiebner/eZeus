#include "emainmenu.h"

#include "ebutton.h"

#include "eframedwidget.h"

#include "elanguage.h"

void addButton(const std::string& text,
               const eAction& a,
               eWidget* const buttons,
               eMainWindow* const window) {
    const auto w1 = new eFramedWidget(window);
    w1->setSmallPadding();
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
    eMainMenuBase::initialize();

    const auto buttons = new eWidget(window());
    addWidget(buttons);

    const auto res = resolution();
    const int cww = res.centralWidgetLargeWidth();
    const int cwh = res.centralWidgetLargeHeight();
    buttons->resize(cww, cwh);

    buttons->align(eAlignment::center);

    addButton(eLanguage::text("new_game"), newGameA, buttons, window());
    addButton(eLanguage::text("load_game"), loadGameA, buttons, window());
    addButton(eLanguage::text("settings"), settingsA, buttons, window());
    addButton(eLanguage::text("quit"), quitA, buttons, window());

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
