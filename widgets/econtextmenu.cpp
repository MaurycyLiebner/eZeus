#include "econtextmenu.h"

#include "textures/egametextures.h"

eContextMenu::eContextMenu(eMainWindow* const window) :
    eFramedWidget(window) {}

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

void eContextMenu::addAction(const std::string& text, const eAction& a) {
    eTexture tex;
    const auto font = eFonts::defaultFont(resolution());
    tex.loadText(renderer(), text, {255, 255, 255, 255}, *font);
    mTextures.push_back(tex);
    mActions.push_back(a);
}

void eContextMenu::sizeHint2(int& w, int& h) {
    const int p = padding();
    h = p;
    w = 0;
    for(const auto& t : mTextures) {
        w = std::max(w, t.width() + p);
        h += t.height() + p;
    }
}

void eContextMenu::paintEvent(ePainter& p) {
    eFramedWidget::paintEvent(p);
//    p.fillRect(rect(), {255, 255, 255, 255});
    const int aCount = mActions.size();
    const int pd = padding();
    const int ah = (height() - 2*pd)/aCount;
    int y = pd;
    const int iMax = mTextures.size();
    for(int i = 0; i < iMax; i++) {
        const auto& t = mTextures[i];
        const auto tw = t.width();
        const auto ww = (width() - tw)/2;
        const SDL_Rect brect{ww, y + ah - pd, width() - 2*ww, 2};
        if(i == mHoverId) {
            p.fillRect(brect, {255, 255, 255, 255});
        }

        const SDL_Rect txtrect{pd, y + pd, width() - 2*pd, ah - 2*pd};
        p.drawTexture(txtrect, t, eAlignment::center);
        y += ah;
    }
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

bool eContextMenu::mouseMoveEvent(const eMouseEvent& e) {
    if(contains(e.x(), e.y())) {
        mHoverId = yToActionId(e.y());
    } else {
        mHoverId = -1;
    }
    return true;
}

int eContextMenu::yToActionId(const int y) const {
    if(y < 0) return -1;
    if(y > height()) return -1;
    const int aCount = mActions.size();
    const int ah = height()/aCount;
    const int id = y/ah;
    if(id < 0) return -1;
    if(id >= aCount) return -1;
    return id;
}

eAction eContextMenu::yToAction(const int y) const {
    const int id = yToActionId(y);
    if(id < 0) return eAction();
    return mActions[id];
}
