#include "econtextmenu.h"

#include "textures/egametextures.h"

eContextMenu::eContextMenu(eMainWindow* const window) :
    eWidget(window) {}

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

void eContextMenu::sizeHint(int& w, int& h) {
    const int p = padding();
    h = p;
    w = 0;
    for(const auto& t : mTextures) {
        w = std::max(w, t.width() + p);
        h += t.height() + p;
    }
    int iRes;
    int dim;
    iResAndDim(iRes, dim);
    h = dim*int(std::ceil((2.*p + h)/dim)) - 2*p;
    w = dim*int(std::ceil((2.*p + w)/dim)) - 2*p;
}

void eContextMenu::paintEvent(ePainter& p) {
    {
        const auto& intrfc = eGameTextures::interface();

        int iRes;
        int dim;
        iResAndDim(iRes, dim);

        const auto& texs = intrfc[iRes].fComboBox[1];

        const int iMax = width()/dim;
        const int jMax = height()/dim;
        for(int i = 0; i < iMax; i++) {
            const int x = dim*i;
            for(int j = 0; j < jMax; j++) {
                const int y = dim*j;
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

void eContextMenu::iResAndDim(int& iRes, int& dim) const {
    const auto res = resolution();
    switch(res) {
    case eRes::p2160:
    case eRes::p1440:
        iRes = 2;
        dim = 32;
        break;
    case eRes::p1080:
    case eRes::p720:
        iRes = 1;
        dim = 16;
        break;
    case eRes::p480:
        iRes = 0;
        dim = 8;
        break;
    }
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
