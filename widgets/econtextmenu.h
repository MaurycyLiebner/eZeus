#ifndef ECONTEXTMENU_H
#define ECONTEXTMENU_H

#include "ewidget.h"

#include "etexture.h"
#include "textures/egametextures.h"

class eContextMenu : public eWidget {
public:
    eContextMenu(eMainWindow* const window);

    void exec();

    void addAction(const std::string& text, const eAction& a);
protected:
    void sizeHint(int& w, int& h);

    void paintEvent(ePainter& p);
    bool mousePressEvent(const eMouseEvent& e);
    bool mouseMoveEvent(const eMouseEvent& e);
private:
    int yToActionId(const int y) const;
    eAction yToAction(const int y) const;

    int mHoverId = -1;

    std::vector<eTexture> mTextures;
    std::vector<eAction> mActions;
};

#endif // ECONTEXTMENU_H
