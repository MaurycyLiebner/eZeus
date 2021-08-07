#ifndef EMAINMENU_H
#define EMAINMENU_H

#include "elabel.h"

class eMainMenu : public eLabel {
public:
    eMainMenu(eMainWindow* const window);

    void initialize(const eAction& newGameA,
                    const eAction& loadGameA,
                    const eAction& settingsA,
                    const eAction& quitA);
private:
    bool mousePressEvent(const eMouseEvent& e);
    bool mouseReleaseEvent(const eMouseEvent& e);
    bool mouseMoveEvent(const eMouseEvent& e);
    bool mouseEnterEvent(const eMouseEvent& e);
    bool mouseLeaveEvent(const eMouseEvent& e);

    bool mPressed = false;
    bool mHover = false;
};

#endif // EMAINMENU_H
