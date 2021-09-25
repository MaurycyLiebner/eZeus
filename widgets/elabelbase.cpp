#include "elabelbase.h"

eLabelBase::eLabelBase(SDL_Renderer* const renderer) :
    mRenderer(renderer) {

}

bool eLabelBase::setFont(const eFont& font) {
    const auto ttf = eFonts::requestFont(font);
    return setFont(ttf);
}

bool eLabelBase::setFontSize(const int s) {
    const auto font = eFonts::defaultFont(s);
    return setFont(font);
}

bool eLabelBase::setFont(TTF_Font* const font) {
    mFont = font;
    return updateTextTexture();
}

bool eLabelBase::setText(const std::string& text) {
    if(text == mText) return true;
    mText = text;
    return updateTextTexture();
}

bool eLabelBase::setTexture(const std::shared_ptr<eTexture>& tex) {
    mTexture = tex;
    return true;
}

bool eLabelBase::setFontColor(const SDL_Color& color) {
    mFontColor = color;
    return updateTextTexture();
}

int eLabelBase::fontSize() const {
    if(!mFont) return 0;
    return TTF_FontHeight(mFont);
}

void eLabelBase::setWrapWidth(const int w) {
    mWidth = w;
    updateTextTexture();
}

bool eLabelBase::updateTextTexture() {
    if(mText.empty()) {
        mTexture.reset();
        return true;
    }
    if(!mFont) return false;
    mTexture = std::make_shared<eTexture>();
    mTexture->loadText(mRenderer, mText, mFontColor, *mFont, mWidth);
    return true;
}
