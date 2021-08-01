#include "elabel.h"

eLabel::eLabel(eMainWindow* const window) :
    eWidget(window) {
    setFont(eFonts::defaultFont(resolution()));
}

eLabel::eLabel(const std::string& text, eMainWindow* const window) :
    eLabel(window) {
    setText(text);
}

bool eLabel::setFont(const eFont& font) {
    const auto ttf = eFonts::requestFont(font);
    return setFont(ttf);
}

bool eLabel::setFont(TTF_Font* const font) {
    mFont = font;
    return updateTextTexture();
}

bool eLabel::setText(const std::string& text) {
    mText = text;
    return updateTextTexture();
}

bool eLabel::setTexture(const eTexture& tex) {
    mTexture = tex;
    return true;
}

bool eLabel::setFontColor(const SDL_Color& color) {
    mFontColor = color;
    return updateTextTexture();
}

bool eLabel::updateTextTexture() {
    if(mText.empty()) {
        mTexture.reset();
        return true;
    }
    if(!mFont) return false;
    mTexture.loadText(renderer(), mText, mFontColor, *mFont);
    return true;
}

void eLabel::sizeHint(int& w, int& h) {
    if(mTexture.isNull()) {
        w = 0;
        h = 0;
    } else {
        w = mTexture.width();
        h = mTexture.height();
    }
}

void eLabel::paintEvent(ePainter& p) {
    if(!mTexture.isNull()) {
        p.drawTexture(rect(), mTexture, eAlignment::center);
    }
}
