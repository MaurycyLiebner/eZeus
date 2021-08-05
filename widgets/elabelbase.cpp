#include "elabelbase.h"

eLabelBase::eLabelBase(SDL_Renderer* const renderer) :
    mRenderer(renderer) {

}

bool eLabelBase::setFont(const eFont& font) {
    const auto ttf = eFonts::requestFont(font);
    return setFont(ttf);
}

bool eLabelBase::setFont(TTF_Font* const font) {
    mFont = font;
    return updateTextTexture();
}

bool eLabelBase::setText(const std::string& text) {
    mText = text;
    return updateTextTexture();
}

bool eLabelBase::setTexture(const eTexture& tex) {
    mTexture = tex;
    return true;
}

bool eLabelBase::setFontColor(const SDL_Color& color) {
    mFontColor = color;
    return updateTextTexture();
}

bool eLabelBase::updateTextTexture() {
    if(mText.empty()) {
        mTexture.reset();
        return true;
    }
    if(!mFont) return false;
    mTexture.loadText(mRenderer, mText, mFontColor, *mFont);
    return true;
}
