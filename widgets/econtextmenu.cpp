#include "econtextmenu.h"

#include "textures/egametextures.h"

eContextMenu::eContextMenu(eMainWindow* const window) :
    eWidget(window) {

}

void eContextMenu::exec() {
    grabMouse();
    grabKeyboard();
    fitContent();
}

void eContextMenu::addAction(const std::string& text, const eAction& a) {
    eTexture tex;
    const auto font = eFonts::defaultFont(resolution());
    tex.loadText(renderer(), text, {0, 0, 0, 255}, *font);
    mTextures.push_back(tex);
    mActions.push_back(a);
}

void eContextMenu::sizeHint(int& w, int& h) {
    const int p = padding();
    h = -2*p;
    for(const auto& t : mTextures) {
        w = std::max(w, t.width() + 2*p);
        h += t.height() + 2*p;
    }
}

void eContextMenu::paintEvent(ePainter& p) {
    {
        const auto& intrfc = eGameTextures::interface();
        const int iMax = width()/32;
        const int jMax = height()/32;
        const auto& texs = intrfc[2].fComboBox[0];
        for(int i = 0; i < iMax; i++) {
            const int x = 32*i;
            for(int j = 0; j < jMax; j++) {
                const int y = 32*j;
                int texId;
                if(i == 0) {
                    if(j == 0) {
                        texId = 0;
                    } else if(j == jMax - 1) {
                        texId = 6;
                    } else {
                        texId = 3;
                    }
                } else if(i == iMax - 1) {
                    if(j == 0) {
                        texId = 2;
                    } else if(j == jMax - 1) {
                        texId = 8;
                    } else {
                        texId = 5;
                    }
                } else if(j == 0) {
                    texId = 1;
                } else if(j == jMax - 1) {
                    texId = 7;
                } else {
                    texId = 4;
                }
                const auto tex = texs.getTexture(texId);
                p.drawTexture(x, y, tex);
            }
        }
    }
//    p.fillRect(rect(), {255, 255, 255, 255});
    const int aCount = mActions.size();
    const int ah = height()/aCount;
    const int pd = padding();
    int y = 0;
    const int iMax = mTextures.size();
    for(int i = 0; i < iMax; i++) {
        const auto& t = mTextures[i];
        const SDL_Rect brect{0, y, width(), ah};
        if(i == mHoverId) {
            p.fillRect(brect, {125, 125, 125, 255});
        }
        p.drawRect(brect, {0, 0, 0, 255}, 2);

        const SDL_Rect txtrect{pd, y + pd, width() - 2*pd, ah - 2*pd};
        p.drawTexture(txtrect, t, eAlignment::left | eAlignment::vcenter);
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
