#include "ebutton.h"

#include <algorithm>
#include <initializer_list>

void eButton::setHoverTexture(const std::shared_ptr<eTexture>& tex) {
    mHoverTexture = tex;
}

void eButton::setPressedTexture(const std::shared_ptr<eTexture>& tex) {
    mPressedTexture = tex;
}

void eButton::setDisabledTexture(const std::shared_ptr<eTexture>& tex) {
    mDisabledTexture = tex;
}

eButton* eButton::sCreate(const eTextureCollection& texs,
                          eMainWindow* const window,
                          eWidget* const buttons) {
    const auto b = sCreateButtonBase<eButton>(texs, window, buttons);
    b->setPressedTexture(texs.getTexture(2));
    return b;
}

void eButton::sizeHint(int& w, int& h) {
    eLabel::sizeHint(w, h);
    const auto& tex = texture();
    w = std::max({w, tex ? tex->width() : 0,
                  mHoverTexture ? mHoverTexture->width() : 0,
                  mPressedTexture ? mPressedTexture->width() : 0});
    h = std::max({h, tex ? tex->height() : 0,
                  mHoverTexture ? mHoverTexture->height() : 0,
                  mPressedTexture ? mPressedTexture->height() : 0});
}

void eButton::paintEvent(ePainter& p) {
    if(!enabled() && mDisabledTexture) {
        p.drawTexture(rect(), mDisabledTexture, eAlignment::center);
    } else if(pressed() && mPressedTexture) {
        p.drawTexture(rect(), mPressedTexture, eAlignment::center);
    } else if(hovered()) {
        if(mHoverTexture) {
            p.drawTexture(rect(), mHoverTexture, eAlignment::center);
        } else {
            eLabel::paintEvent(p);
            const auto& t = texture();
            if(!t) return;
            const int tw = t->width();
            const int ww = (width() - tw)/2;
            const int th = t->height();
            const int hh = (height() - th)/2;
            const int ah = height();

            SDL_Color col1;
            SDL_Color col2;
            eFontColorHelpers::colors(fontColor(), col1, col2);
            const SDL_Rect rect2{ww, ah - hh,
                                 width() - 2*ww,
                                 lineWidth()};
            const SDL_Rect rect1{rect2.x + 1, rect2.y + 1,
                                 rect2.w, rect2.h};
            p.fillRect(rect2, col2);
            p.fillRect(rect1, col1);
        }
    } else {
        eLabel::paintEvent(p);
    }
}
