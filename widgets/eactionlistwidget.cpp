#include "eactionlistwidget.h"


void eActionListWidget::addAction(
        const std::string& text, const eAction& a) {
    eTexture tex;
    const auto font = eFonts::defaultFont(mFontSize);
    tex.loadText(renderer(), text, {255, 255, 255, 255}, *font);
    mTextures.push_back(tex);
    mActions.push_back(a);
}

void eActionListWidget::setSmallFontSize() {
    mFontSize = eResolution::smallFontSize(resolution());
}

void eActionListWidget::sizeHint2(int& w, int& h) {
    const int p = padding();
    h = p;
    w = 0;
    for(const auto& t : mTextures) {
        w = std::max(w, t.width() + p);
        h += t.height() + p;
    }
}

void eActionListWidget::paintEvent(ePainter& p) {
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

bool eActionListWidget::mousePressEvent(const eMouseEvent& e) {
    (void)e;
    if(contains(e.x(), e.y())) {
        const auto a = yToAction(e.y());
        a();
    }
    return true;
}

bool eActionListWidget::mouseMoveEvent(const eMouseEvent& e) {
    if(contains(e.x(), e.y())) {
        mHoverId = yToActionId(e.y());
    } else {
        mHoverId = -1;
    }
    return true;
}

int eActionListWidget::yToActionId(const int y) const {
    if(y < 0) return -1;
    if(y > height()) return -1;
    const int aCount = mActions.size();
    const int ah = height()/aCount;
    const int id = y/ah;
    if(id < 0) return -1;
    if(id >= aCount) return -1;
    return id;
}

eAction eActionListWidget::yToAction(const int y) const {
    const int id = yToActionId(y);
    if(id < 0) return eAction();
    return mActions[id];
}
