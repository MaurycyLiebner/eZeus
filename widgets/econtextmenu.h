#ifndef ECONTEXTMENU_H
#define ECONTEXTMENU_H

#include "ewidget.h"

#include "etexture.h"

class eContextMenu : public eWidget {
public:
    eContextMenu(SDL_Renderer* const renderer);

    void exec();

    void addAction(const std::string& text, const eAction& a);
protected:
    void paintEvent(ePainter& p);
    bool mousePressEvent(const eMouseEvent& e);
private:
    eAction yToAction(const int y) const;

    std::vector<eTexture> mTextures;
    std::vector<eAction> mActions;
};

#endif // ECONTEXTMENU_H
