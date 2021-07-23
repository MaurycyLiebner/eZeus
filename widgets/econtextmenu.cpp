#include "econtextmenu.h"

eContextMenu::eContextMenu(SDL_Renderer* const renderer) :
    eWidget(renderer) {

}

void eContextMenu::exec() {
    grabMouse();
    grabKeyboard();
}

void eContextMenu::addAction(const std::string& text, const eAction& a) {
    eTexture tex;
    tex.loadText(renderer(), text, {0, 0, 0, 255}, {"fonts/FreeSans.ttf", 28});
    mTextures.push_back(tex);
    mActions.push_back(a);
    setHeight(50*mActions.size());
}

void eContextMenu::paintEvent(ePainter& p) {
    const int aCount = mActions.size();
    const int ah = height()/aCount;
    int y = 0;
    for(const auto& t : mTextures) {
        const SDL_Rect txtrect{25, y, width(), ah};
        p.drawTexture(txtrect, t, eAlignment::left | eAlignment::vcenter);
        const SDL_Rect brect{0, y, width(), ah};
        p.drawRect(brect, {0, 0, 0, 255}, 2);
        y += ah;
    }
    p.drawRect(rect(), {0, 0, 0, 255}, 2);
}

bool eContextMenu::mousePressEvent(const eMouseEvent& e) {
    (void)e;
    if(contains(e.x(), e.y())) {
        const auto a = yToAction(e.y());
        a();
    }
    deleteLater();
    return true;
}

eAction eContextMenu::yToAction(const int y) const {
    if(y < 0) return eAction();
    if(y > height()) return eAction();
    const int aCount = mActions.size();
    const int ah = height()/aCount;
    const int id = y/ah;
    if(id < 0) return eAction();
    if(id >= aCount) return eAction();
    return mActions[id];
}
