#include "ebutton.h"

eButton::eButton(SDL_Renderer* const renderer) :
    eWidget(renderer) {
    setFont({"fonts/FreeSans.ttf", 28});
}

bool eButton::setFont(const eFont& font) {
    const auto ttf = eFonts::requestFont(font);
    return setFont(ttf);
}

bool eButton::setFont(TTF_Font* const font) {
    mFont = font;
    return updateTextTexture();
}

bool eButton::setText(const std::string& text) {
    mText = text;
    return updateTextTexture();
}

bool eButton::setFontColor(const SDL_Color& color) {
    mFontColor = color;
    return updateTextTexture();
}

bool eButton::updateTextTexture() {
    if(mText.empty()) {
        mTextTex.reset();
        return true;
    }
    if(!mFont) return false;
    mTextTex.loadText(renderer(), mText, mFontColor, *mFont);
    return true;
}

void eButton::paintEvent(ePainter& p) {
    p.drawRect(rect(), {0, 0, 0, 255}, 5);
    if(mPressed && !mPressedTexture.isNull()) {
        p.drawTexture(rect(), mPressedTexture, eAlignment::center);
    } else if(mHover && !mHoverTexture.isNull()) {
        p.drawTexture(rect(), mHoverTexture, eAlignment::center);
    } else if(!mTexture.isNull()) {
        p.drawTexture(rect(), mTexture, eAlignment::center);
    }
    if(!mTextTex.isNull()) {
        p.drawTexture(rect(), mTextTex, eAlignment::center);
    }
}

bool eButton::mousePressEvent(const eMouseEvent& e) {
    (void)e;
    mPressed = true;
    return true;
}

bool eButton::mouseReleaseEvent(const eMouseEvent& e) {
    (void)e;
    mPressed = false;
    return true;
}

bool eButton::mouseMoveEvent(const eMouseEvent& e) {
    (void)e;
    return true;
}

bool eButton::mouseEnterEvent(const eMouseEvent& e) {
    (void)e;
    mHover = true;
    return true;
}

bool eButton::mouseLeaveEvent(const eMouseEvent& e) {
    (void)e;
    mHover = false;
    return true;
}
