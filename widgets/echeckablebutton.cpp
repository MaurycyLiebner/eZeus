#include "echeckablebutton.h"

eCheckableButton::eCheckableButton(eMainWindow* const window) :
    eButton(window) {
    setPressAction([this]() {
        mChecked = !mChecked;
    });
}

void eCheckableButton::setCheckAction(const eCheckAction& a) {
    setPressAction([this, a]() {
        mChecked = !mChecked;
        a(mChecked);
    });
}

void eCheckableButton::setChecked(const bool c) {
    mChecked = c;
}

void eCheckableButton::setCheckedTexture(const std::shared_ptr<eTexture>& tex) {
    mCheckedTexture = tex;
}

eCheckableButton* eCheckableButton::sCreate(
        const eTextureCollection& texs,
        eMainWindow* const window,
        eWidget* const buttons) {
    const auto b = sCreateButtonBase<eCheckableButton>(texs, window, buttons);
    b->setCheckedTexture(texs.getTexture(2));
    return b;
}

void eCheckableButton::paintEvent(ePainter& p) {
    if(mCheckedTexture) {
        if(mChecked) {
            p.drawTexture(rect(), mCheckedTexture, eAlignment::center);
        } else eButton::paintEvent(p);
    } else {
        eButton::paintEvent(p);
        if(mChecked) p.drawRect(rect(), fontColor(), lineWidth());
    }
}
