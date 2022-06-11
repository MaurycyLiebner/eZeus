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
        if(mChecked) {
            SDL_Color col1;
            SDL_Color col2;
            eFontColorHelpers::colors(fontColor(), col1, col2);
            const SDL_Rect rect2{rect()};
            const SDL_Rect rect1{rect2.x + 1, rect2.y + 1,
                                 rect2.w, rect2.h};
            p.drawRect(rect2, col2, lineWidth());
            p.drawRect(rect1, col1, lineWidth());
        }
    }
}
