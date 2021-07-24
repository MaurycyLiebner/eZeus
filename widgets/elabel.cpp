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

bool eLabel::setFontColor(const SDL_Color& color) {
    mFontColor = color;
    return updateTextTexture();
}

bool eLabel::updateTextTexture() {
    if(mText.empty()) {
        mTextTex.reset();
        return true;
    }
    if(!mFont) return false;
    mTextTex.loadText(renderer(), mText, mFontColor, *mFont);
    return true;
}

void eLabel::sizeHint(int& w, int& h) {
    if(mTextTex.isNull()) {
        w = 0;
        h = 0;
    } else {
        w = mTextTex.width();
        h = mTextTex.height();
    }
}

void eLabel::paintEvent(ePainter& p) {
    if(!mTextTex.isNull()) {
        p.drawTexture(rect(), mTextTex, eAlignment::center);
    }
}
