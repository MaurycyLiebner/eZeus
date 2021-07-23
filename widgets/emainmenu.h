#ifndef EMAINMENU_H
#define EMAINMENU_H

#include "ewidget.h"

class eMainMenu : public eWidget {
public:
    eMainMenu(SDL_Renderer* const renderer);

    void initialize();
private:
    void paintEvent(ePainter& p);

    bool mousePressEvent(const eMouseEvent& e);
    bool mouseReleaseEvent(const eMouseEvent& e);
    bool mouseMoveEvent(const eMouseEvent& e);
    bool mouseEnterEvent(const eMouseEvent& e);
    bool mouseLeaveEvent(const eMouseEvent& e);

    bool mPressed = false;
    bool mHover = false;
};

#endif // EMAINMENU_H
