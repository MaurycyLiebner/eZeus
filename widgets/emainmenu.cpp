#include "emainmenu.h"

#include "ebutton.h"
#include "eframedbutton.h"

#include "eframedwidget.h"
#include "enamewidget.h"
#include "elanguage.h"
#include "emainwindow.h"
#include "engine/eworldcity.h"

void addButton(const std::string& text,
               const eAction& a,
               eWidget* const buttons,
               eMainWindow* const window) {
    const auto b1 = new eFramedButton(window);
    b1->setRenderBg(true);
    b1->setUnderline(false);
    buttons->addWidget(b1);
    b1->setPressAction(a);
    b1->setText(text);
    b1->fitContent();
    b1->align(eAlignment::hcenter);
}

void eMainMenu::initialize(const eAction& newGameA,
                           const eAction& loadGameA,
                           const eAction& editGameA,
                           const eAction& settingsA,
                           const eAction& quitA,
                           const eAction& leaderA) {
    eMainMenuBase::initialize();

    const auto w = window();

    const auto buttons = new eWidget(w);
    addWidget(buttons);

    const auto res = resolution();
    const int cww = res.centralWidgetLargeWidth();
    const int cwh = res.centralWidgetLargeHeight();
    buttons->resize(cww, cwh);

    buttons->align(eAlignment::center);

    addButton(eLanguage::zeusText(1, 1), newGameA, buttons, w);
    addButton(eLanguage::zeusText(1, 3), loadGameA, buttons, w);
    addButton(eLanguage::zeusText(287, 3), editGameA, buttons, w);
    addButton(eLanguage::zeusText(2, 0), settingsA, buttons, w);
    addButton(eLanguage::zeusText(1, 5), quitA, buttons, w);

    buttons->layoutVertically();

    const auto leader = new eFramedButton(w);
    leader->setRenderBg(true);
    leader->setUnderline(false);
    leader->setPressAction(leaderA);
    leader->setText(w->leader());
    leader->fitContent();
    addWidget(leader);
    const int p = res.hugePadding();
    int tw;
    int th;
    textureSize(tw, th);
    leader->setX((width() - tw)/2 + 2*p);
    leader->setY(2*p);
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
