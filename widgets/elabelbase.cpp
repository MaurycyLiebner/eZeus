#include "elabelbase.h"

#include "emainwindow.h"

eLabelBase::eLabelBase(eMainWindow* const window) :
    mWindow(window) {

}

bool eLabelBase::setFont(const eFont& font) {
    const auto ttf = eFonts::requestFont(font);
    return setFont(ttf);
}

bool eLabelBase::setTinyFontSize() {
    const int s = res().tinyFontSize();
    return setFontSize(s);
}

bool eLabelBase::setVerySmallFontSize() {
    const int s = res().verySmallFontSize();
    return setFontSize(s);
}

bool eLabelBase::setSmallFontSize() {
    const int s = res().smallFontSize();
    return setFontSize(s);
}

bool eLabelBase::setHugeFontSize() {
    const int s = res().hugeFontSize();
    return setFontSize(s);
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

bool eLabelBase::setFontColor(const eFontColor color) {
    mFontColor = color;
    return updateTextTexture();
}

void eLabelBase::setLightFontColor() {
    setFontColor(eFontColor::light);
}

void eLabelBase::setDarkFontColor() {
    setFontColor(eFontColor::dark);
}

void eLabelBase::setYellowFontColor() {
    setFontColor(eFontColor::yellow);
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
    const auto r = mWindow->renderer();
    mTexture->loadText(r, mText, mFontColor, *mFont, mWidth, mWrapAlign);
    return true;
}

const eResolution& eLabelBase::res() const {
    return mWindow->resolution();
}

int eLabelBase::lineWidth() const {
    return std::max(1, fontSize()/15);
}
