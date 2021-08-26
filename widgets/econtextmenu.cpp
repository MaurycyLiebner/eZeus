#include "econtextmenu.h"

#include "textures/egametextures.h"

void eContextMenu::exec(const int x, const int y,
                        eWidget* const w) {
    int gx = x;
    int gy = y;
    w->mapToGlobal(gx, gy);
    move(gx, gy);
    w->lastAncestor()->addWidget(this);

    grabMouse();
    grabKeyboard();
    fitContent();
}

bool eContextMenu::mouseReleaseEvent(const eMouseEvent& e) {
    eActionListWidget::mouseReleaseEvent(e);
    deleteLater();
    return true;
}
