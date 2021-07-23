#include "elabel.h"

eLabel::eLabel(SDL_Renderer* const renderer) :
    eWidget(renderer) {
    setFont({"fonts/FreeSans.ttf", 28});
}

eLabel::eLabel(const std::string& text, SDL_Renderer* const renderer) :
    eLabel(renderer) {
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

void eLabel::fitSizeToText(const int padding) {
    if(mTextTex.isNull()) return;
    const int w = 2*padding + mTextTex.width();
    const int h = 2*padding + mTextTex.height();
    resize(w, h);
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

void eLabel::paintEvent(ePainter& p) {
    if(!mTextTex.isNull()) {
        p.drawTexture(rect(), mTextTex, eAlignment::center);
    }
}
