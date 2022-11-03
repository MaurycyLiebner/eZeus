#include "eactionlistwidget.h"

#include "audio/esounds.h"

std::shared_ptr<eTexture> eActionListWidget::textToTexture(const std::string& text) {
    const auto tex = std::make_shared<eTexture>();
    const auto font = eFonts::defaultFont(mFontSize);
    tex->loadText(renderer(), text, eFontColor::light, *font);
    return tex;
}

eActionInstance& eActionListWidget::addAction(
        const std::string& text, const eAction& a) {
    auto& ai = mActions.emplace_back(this, a);
    ai.addText(0, text);
    return ai;
}

void eActionListWidget::setSmallFontSize() {
    mFontSize = resolution().smallFontSize();
}

void eActionListWidget::sizeHint(int& w, int& h) {
    const int p = padding();
    h = p;
    w = 0;
    for(const auto& t : mActions) {
        w = std::max(w, t.width() + p);
        h += t.height() + p;
    }
}

void eActionListWidget::paintEvent(ePainter& p) {
    eFramedWidget::paintEvent(p);
    //    p.fillRect(rect(), {255, 255, 255, 255});
    const int aCount = mActions.size();
    if(aCount == 0) return;
    const int pd = padding();
    const int ah = (height() - 2*pd)/aCount;
    int y = pd;
    const int iMax = mActions.size();
    for(int i = 0; i < iMax; i++) {
        const auto& t = mActions[i];
        const auto tw = t.width();
        const auto ww = (width() - tw)/2;
        const SDL_Rect brect{ww, y + ah - pd, width() - 2*ww, 2};
        if(i == mHoverId) {
            p.fillRect(brect, {255, 255, 255, 255});
        }
        const SDL_Rect arect{ww, y + pd, tw, ah - 2*pd};
        t.draw(p, arect);
        y += ah;
    }
}

bool eActionListWidget::mousePressEvent(const eMouseEvent& e) {
    (void)e;
    return true;
}

bool eActionListWidget::mouseReleaseEvent(const eMouseEvent& e) {
    (void)e;
    if(contains(e.x(), e.y())) {
        const auto a = yToAction(e.y());
        if(a) a();
    }
    eSounds::playButtonSound();
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
    return mActions[id].action();
}

eActionInstance::eActionInstance(eActionListWidget* const parent,
                                 const eAction& a) :
    mParent(parent), mAction(a) {}

int eActionInstance::width() const {
    int result = 0;
    const int iMax = mTextures.size();
    for(int i = 0; i < iMax; i++) {
        const int margin = mMargins[i];
        const auto& t = mTextures[i];
        result += margin + t->width();
    }
    return result;
}

int eActionInstance::height() const {
    int result = 0;
    for(const auto& t : mTextures) {
        result = std::max(result, t->height());
    }
    return result;
}

void eActionInstance::addText(const int margin, const std::string& text) {
    const auto tex = mParent->textToTexture(text);
    addTexture(margin, tex);
}

void eActionInstance::addTexture(const int margin, const std::shared_ptr<eTexture>& tex) {
    mMargins.push_back(margin);
    mTextures.push_back(tex);
}

const eAction& eActionInstance::action() const { return mAction; }

void eActionInstance::draw(ePainter& p, const SDL_Rect& rect) const {
    int x = rect.x;
    const int iMax = mTextures.size();
    for(int i = 0; i < iMax; i++) {
        x += mMargins[i];
        const auto& tt = mTextures[i];
        const int ttw = tt->width();
        p.drawTexture({x, rect.y, ttw, rect.h}, tt, eAlignment::center);
        x += ttw;
    }
}
